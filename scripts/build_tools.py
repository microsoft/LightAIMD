#!/usr/bin/env python3
import os
import sys
import platform
import subprocess
from config import *


def linux_distro():
    if os.path.exists("/etc/os-release"):
        with open("/etc/os-release", "r") as f:
            for line in f:
                if line.startswith("ID="):
                    return line[3:].strip()

    return "unknown"


def find_executable(executable):
    if not os.path.exists("/usr/bin/which"):
        raise Exception("'/usr/bin/which' is not found, please install it first")

    return (
        subprocess.run(
            ["which", executable], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL
        )
        .stdout.decode("utf-8")
        .strip()
    )


def find_package_manager():
    if find_executable("apt") != "":
        config["package_manager"] = "apt"
    elif find_executable("dnf") != "":
        config["package_manager"] = "dnf"
    elif find_executable("zypper") != "":
        config["package_manager"] = "zypper"
    elif find_executable("pacman") != "":
        config["package_manager"] = "pacman"
    else:
        config["package_manager"] = "unknown"


def check_update():
    if config["dry_run"]:
        return

    if config["package_manager"] == "apt":
        subprocess.run(
            ["sudo", "apt", "update", "-qq"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    elif config["package_manager"] == "dnf":
        subprocess.run(
            ["sudo", "dnf", "check-update", "-q"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    elif config["package_manager"] == "zypper":
        subprocess.run(
            ["sudo", "zypper", "--quiet", "refresh"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    elif config["package_manager"] == "pacman":
        subprocess.run(
            ["sudo", "pacman", "-Sy"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
        )
    else:
        raise Exception("Unknown package manager")


def is_package_installed(package_name):
    if config["package_manager"] == "apt":
        output = subprocess.run(
            ["apt", "-qq", "list", "--installed", package_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
        ).stdout.decode("utf-8")
        return "[installed]" in output
    elif config["package_manager"] == "dnf":
        output = subprocess.run(
            ["dnf", "list", "--installed", package_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
        ).stdout.decode("utf-8")
        return package_name in output
    elif config["package_manager"] == "zypper":
        output = subprocess.run(
            ["zypper", "search", "-i", package_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
        ).stdout.decode("utf-8")
        return package_name in output
    elif config["package_manager"] == "pacman":
        output = subprocess.run(
            ["pacman", "-Q", package_name],
            stdout=subprocess.PIPE,
            stderr=subprocess.DEVNULL,
        ).stdout.decode("utf-8")
        return package_name in output
    else:
        raise Exception("Unknown package manager")


def install_packages(package_names):
    if config["dry_run"]:
        return

    packages = []
    for pkg in package_names:
        if is_package_installed(pkg):
            continue
        packages.append(pkg)

    if len(packages) == 0:
        return

    if config["package_manager"] == "apt":
        subprocess.run(
            ["sudo", "apt", "install", "-qq", "-y"] + packages,
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
        )
    elif config["package_manager"] == "dnf":
        subprocess.run(
            ["sudo", "dnf", "install", "-q", "-y"] + packages,
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
        )
    elif config["package_manager"] == "zypper":
        subprocess.run(
            ["sudo", "zypper", "--quiet", "install", "-y"] + packages,
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
        )
    elif config["package_manager"] == "pacman":
        subprocess.run(
            ["sudo", "pacman", "-S", "--noconfirm"] + packages,
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
        )
    else:
        print("Unknown package manager")
        sys.exit(1)


def install_build_tools():
    """
    Check if the prerequisites are installed.
    """
    if not os.path.exists("/usr/bin/sudo"):
        print("The 'sudo' command is not found, please install it first")
        sys.exit(1)

    if not os.path.exists("/usr/bin/which"):
        print(
            "The 'which' command ('/usr/bin/which') is not found, please install it first"
        )
        sys.exit(1)

    required_tools = [
        "git",
        "curl",
        "tar",
        "make",
        "gcc",
        "g++",
        "gfortran",
        "ninja"
    ]

    if config["COMPILER"] == "clang":
        required_tools += ["clang", "clang++"]

    missing_tools = []

    for tool in required_tools:
        if find_executable(tool) == "":
            missing_tools.append(tool)

    if len(missing_tools) == 0:
        print("All required tools are installed")
        return

    print(
        "The following tools are required but not found: {}".format(
            ", ".join(missing_tools)
        )
    )
    find_package_manager()
    if config["package_manager"] == "unknown":
        print("Cannot find a supported package manager, please install them manually")
        return

    print("Do you want to install them? (y/n)")
    answer = input()
    if answer != "y":
        print("Aborted")
        sys.exit()

    check_update()

    print("Installing build tools...")

    if config["package_manager"] == "apt":
        install_packages(["build-essential", "gfortran", "clang", "ninja-build"])
    elif config["package_manager"] == "dnf":
        install_packages(
            [
                "git",
                "curl",
                "tar",
                "make",
                "gcc",
                "gcc-c++",
                "gcc-gfortran",
                "clang",
                "ninja-build",
            ]
        )
    elif config["package_manager"] == "zypper":
        install_packages(["git", "make", "gcc", "gcc-c++", "gcc-fortran", "ninja"])
    elif config["package_manager"] == "pacman":
        install_packages(["git", "make", "gcc", "gcc-fortran", "ninja"])
    else:
        print("Unknown package manager")
        sys.exit(1)

    print("Build tools installed")
