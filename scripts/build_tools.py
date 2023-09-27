#!/usr/bin/env python3
import os
import platform
import subprocess
from config import *


def linux_distro():
    return platform.freedesktop_os_release()["ID"]


def find_executable(executable):
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
    else:
        raise Exception("Unknown package manager")


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
    else:
        raise Exception("Unknown package manager")


def install_build_tools():
    find_package_manager()

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
    else:
        raise Exception("Unknown package manager")

    print("Build tools installed")
