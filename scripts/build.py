#!/usr/bin/env python3
import os
import sys
import subprocess

from config import *
from build_tools import *
from toolchain import *
from ninja_generator import *
from sanity_tests import *


def main():
    import argparse

    parser = argparse.ArgumentParser()

    cuda_group = parser.add_mutually_exclusive_group()
    cuda_group.add_argument(
        "--enable-cuda",
        dest="enable_cuda",
        default=True,
        required=False,
        action="store_true",
        help="Enable CUDA",
    )
    cuda_group.add_argument(
        "--disable-cuda",
        dest="disable_cuda",
        default=False,
        required=False,
        action="store_true",
        help="Disable CUDA",
    )

    parser.add_argument(
        "--use-mkl",
        dest="use_mkl",
        default=False,
        required=False,
        action="store_true",
        help="Use MKL",
    )

    parser.add_argument(
        "--compiler",
        dest="compiler",
        default="gcc",
        required=False,
        choices=["clang", "gcc", "icx"],
        help="Compiler to use",
    )
    parser.add_argument(
        "--install-build-tools",
        dest="install_build_tools",
        default=False,
        required=False,
        action="store_true",
        help="Setup the build tools",
    )
    parser.add_argument(
        "--build",
        dest="build",
        default=False,
        required=False,
        action="store_true",
        help="Build the project",
    )
    parser.add_argument(
        "--clean",
        dest="clean",
        default=False,
        required=False,
        action="store_true",
        help="Clean the project",
    )
    parser.add_argument(
        "--rebuild",
        dest="rebuild",
        default=False,
        required=False,
        action="store_true",
        help="Rebuild the project",
    )
    parser.add_argument(
        "--reset",
        dest="reset",
        default=False,
        required=False,
        action="store_true",
        help="Reset the project: remove all build files and the installed third party libraries",
    )
    #
    parser.add_argument(
        "--debug",
        dest="debug",
        default=False,
        required=False,
        action="store_true",
        help="Build the debug version of the project",
    )
    parser.add_argument(
        "--release",
        dest="release",
        default=False,
        required=False,
        action="store_true",
        help="Build the release version of the project",
    )
    #
    parser.add_argument(
        "--run",
        dest="run",
        default="",
        required=False,
        help="Run an executable",
    )
    #
    parser.add_argument(
        "--sanity-test",
        dest="sanity_test",
        default=False,
        required=False,
        action="store_true",
        help="Run the sanity tests",
    )
    parser.add_argument(
        "--module-test",
        dest="module_test",
        default=False,
        required=False,
        action="store_true",
        help="Run the module tests",
    )
    #
    parser.add_argument(
        "--verbose",
        dest="verbose",
        default=False,
        required=False,
        action="store_true",
        help="Verbose output",
    )
    parser.add_argument(
        "--quiet",
        dest="quiet",
        default=False,
        required=False,
        action="store_true",
        help="Quiet output",
    )
    parser.add_argument(
        "--assume-yes",
        dest="assume_yes",
        default=False,
        required=False,
        action="store_true",
        help="Assume yes as answer to all prompts",
    )
    parser.add_argument(
        "--dry-run",
        dest="dry_run",
        default=False,
        required=False,
        action="store_true",
        help="Dry run",
    )
    args = parser.parse_args()

    if args.verbose:
        config["verbose"] = True

    if args.quiet:
        config["quiet"] = True

    if args.assume_yes:
        config["assume_yes"] = True
    else:
        config["assume_yes"] = False

    if args.dry_run:
        print("Running in dry run mode")
        config["dry_run"] = True

    if args.compiler:
        config["COMPILER"] = args.compiler

    if args.enable_cuda:
        config["DISABLE_CUDA"] = False

    if args.disable_cuda:
        config["DISABLE_CUDA"] = True

    if args.use_mkl:
        config["USE_MKL"] = True
        config["SHARED_LIBS"].extend(["mkl_intel_lp64", "mkl_sequential", "mkl_core"])
    else:
        config["USE_MKL"] = False
        config["SHARED_LIBS"].append("lapacke")

    if not args.debug and not args.release:
        args.release = True

    if args.clean:
        clean()

    if args.reset:
        reset()

    if args.install_build_tools:
        install_build_tools()

    if args.build:
        setup_toolchain()
        if args.debug:
            build_debug()
        if args.release:
            build_release()

    if args.rebuild:
        setup_toolchain()
        clean()
        if args.debug:
            build_debug()
        if args.release:
            build_release()

    if args.run:
        run(args)

    if args.sanity_test:
        setup_toolchain()
        passed = run_sanity_tests(args)
        if passed:
            print("Sanity tests passed")
            return 0
        else:
            print("Sanity tests failed")
            return 1

    if args.module_test:
        if args.debug:
            module_test_debug()
        if args.release:
            module_test_release()

    return 0


def reset():
    print(
        "Resetting the project to the initial state.\nAll the build files and the installed third party libraries will be removed ..."
    )
    if config["dry_run"]:
        return

    import shutil

    remove_installed_third_parties()
    if os.path.exists(config["build_root_dir"]):
        shutil.rmtree(config["build_root_dir"])


def clean():
    print("Cleaning the build directory")
    if config["dry_run"]:
        return

    if os.path.exists(config["active_build_dir"]):
        subprocess.run(
            ["ninja", "-t", "clean"], cwd=config["active_build_dir"], check=True
        )


def build_release():
    print("Building release version")
    config["active_build_dir"] = config["build_release_dir"]
    build(debug=False)


def build_debug():
    print("Building debug version")
    config["active_build_dir"] = config["build_debug_dir"]
    build(debug=True)


def build(debug=False):
    if config["dry_run"]:
        return

    config["bin_dir"] = os.path.join(config["active_build_dir"], "bin")
    config["lib_dir"] = os.path.join(config["active_build_dir"], "lib")
    config["obj_dir"] = os.path.join(config["active_build_dir"], "obj")

    generate_ninja_script(debug=debug)
    subprocess.run(
        ["ninja", "-f", os.path.join(config["active_build_dir"], "build.ninja")],
        cwd=config["active_build_dir"],
        check=True,
    )


def run(args):
    executable = args.run.strip()

    if executable == "":
        print("No executable specified")
        return

    if args.debug:
        config["active_build_dir"] = config["build_debug_dir"]
        config["bin_dir"] = os.path.join(config["active_build_dir"], "bin")
        print("Running the debug version:")
        print(f"    {os.path.join(config['bin_dir'], executable)}")
        if config["dry_run"]:
            return

        subprocess.run(
            [os.path.join(config["bin_dir"], executable)],
            cwd=config["root_dir"],
            check=True,
        )

    if args.release:
        config["active_build_dir"] = config["build_release_dir"]
        config["bin_dir"] = os.path.join(config["active_build_dir"], "bin")
        print("Running the release version:")
        print(f"    {os.path.join(config['bin_dir'], executable)}")
        if config["dry_run"]:
            return

        subprocess.run(
            [os.path.join(config["bin_dir"], executable)],
            cwd=config["root_dir"],
            check=True,
        )


def module_test_debug():
    print("Running the debug version of module tests")
    config["active_build_dir"] = config["build_debug_dir"]
    config["bin_dir"] = os.path.join(config["active_build_dir"], "bin")
    module_test()


def module_test_release():
    print("Running the release version of module tests")
    config["active_build_dir"] = config["build_release_dir"]
    config["bin_dir"] = os.path.join(config["active_build_dir"], "bin")
    module_test()


def module_test():
    for root, dirs, files in os.walk(config["bin_dir"]):
        for f in files:
            print(f"Running module test: {root}/{f}")
            if config["dry_run"]:
                continue
            try:
                if (
                    subprocess.run(
                        [os.path.join(root, f)], cwd=config["root_dir"], check=True
                    ).returncode
                    != 0
                ):
                    print(f"Module test: {f} failed\n")
                    sys.exit(1)
            except:
                print(f"Module test: {f} failed\n")
                sys.exit(1)
            print(f"Finished module test: {f}\n")

    print("All module tests passed\n")


if __name__ == "__main__":
    exit_code = main()
    sys.exit(exit_code)
