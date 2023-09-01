#!/usr/bin/env python3
import subprocess

from config import *

__all__ = ["run_sanity_tests"]

energies_comparison = [
    "{active_build_dir}/bin/{platform}/lightaimd --hf --silent --check-results 1",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --xc-functional 1,7 --silent --check-results 2",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --xc-functional 101,130 --silent --check-results 3",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --xc-functional 402 --silent --check-results 4",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --xc-functional 203,233 --silent --check-results 5",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --xc-functional 450,236 --silent --check-results 6",
]

energies_forces_comparison = [
    "{active_build_dir}/bin/{platform}/lightaimd --hf --spf --silent --check-results 1",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --spf --xc-functional 1,7 --silent --check-results 2",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --spf --xc-functional 101,130 --silent --check-results 3",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --spf --xc-functional 402 --silent --check-results 4",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --spf --xc-functional 203,233 --silent --check-results 5",
    "{active_build_dir}/bin/{platform}/lightaimd --dft --spf --xc-functional 450,236 --silent --check-results 6",
]


def run_sanity_tests(args):
    debug_result = True
    release_result = True
    if args.debug:
        config["active_build_dir"] = config["build_debug_dir"]
        debug_result = sanity_tests()

    if args.release:
        config["active_build_dir"] = config["build_release_dir"]
        release_result = sanity_tests()

    return debug_result and release_result


def sanity_tests():
    passed = True
    for cmd in energies_comparison:
        cmd = cmd.format(active_build_dir=config["active_build_dir"], platform="cuda" if config["use_cuda"] else "cpu")
        output = subprocess.run(
            cmd,
            cwd=config["root_dir"],
            shell=True,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        ).stdout.decode("utf-8")
        print(output)
        if "Failed" in output:
            passed = False

    for cmd in energies_forces_comparison:
        cmd = cmd.format(active_build_dir=config["active_build_dir"], platform="cuda" if config["use_cuda"] else "cpu")
        output = subprocess.run(
            cmd,
            cwd=config["root_dir"],
            shell=True,
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
        ).stdout.decode("utf-8")
        print(output)
        if "Failed" in output:
            passed = False

    return passed
