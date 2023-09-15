#!/usr/bin/env python3
import os
import subprocess

from config import *
from toolchain import *
from ninja_generator import *
from sanity_tests import *


def main():
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--compiler",
        dest="compiler",
        default="clang",
        required=False,
        choices=["clang", "gcc", "icx"],
        help="Compiler to use",
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
        default=True,
        required=False,
        action="store_true",
        help="Build the release version of the project",
    )
    #
    parser.add_argument(
        "--run",
        dest="run",
        default=False,
        required=False,
        action="store_true",
        help="Run the project",
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

    if args.dry_run:
        config["dry_run"] = True

    if args.compiler:
        config["COMPILER"] = args.compiler

    if args.clean:
        clean()

    if args.reset:
        reset()

    if args.build:
        setup_toolchain()
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
        module_test()

    return 0


def reset():
    import shutil

    remove_installed_third_parties()
    if os.path.exists(config["build_root_dir"]):
        shutil.rmtree(config["build_root_dir"])


def clean():
    subprocess.run(["ninja", "-t", "clean"], cwd=config["active_build_dir"], check=True)


def build_release():
    config["active_build_dir"] = config["build_release_dir"]
    build(debug=False)


def build_debug():
    config["active_build_dir"] = config["build_debug_dir"]
    build(debug=True)


def build(debug=False):
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
    if args.debug:
        config["active_build_dir"] = config["build_debug_dir"]
        subprocess.run(
            [os.path.join(config["bin_dir"], "lightaimd")],
            cwd=config["root_dir"],
            check=True,
        )

    if args.release:
        config["active_build_dir"] = config["build_release_dir"]
        subprocess.run(
            [os.path.join(config["bin_dir"], "lightaimd")],
            cwd=config["root_dir"],
            check=True,
        )


def module_test():
    for root, dirs, files in os.walk(config["bin_dir"]):
        for f in files:
            print(f"Running {f}")
            subprocess.run([os.path.join(root, f)], cwd=config["root_dir"], check=True)


if __name__ == "__main__":
    from sys import exit

    exit_code = main()
    exit(exit_code)
