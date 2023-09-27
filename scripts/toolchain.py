#!/usr/bin/env python3
import os
import subprocess
from config import *
from build_tools import *

__all__ = ["setup_toolchain", "remove_installed_third_parties"]


def find_compilers():
    find_CC()
    find_CXX()
    check_clang_selected_gcc()
    find_nvcc()


def find_nvcc():
    config["NVCC"] = find_executable("nvcc")

    if config["NVCC"] == "":
        # Try to find nvcc in the default CUDA installation path
        default_nvcc_path = "/usr/local/cuda/bin/nvcc"
        if os.path.exists(default_nvcc_path):
            config["NVCC"] = default_nvcc_path

    nvidia_smi = find_executable("nvidia-smi")

    if nvidia_smi != "":
        compute_cap = (
            subprocess.run(
                [
                    "sudo",
                    nvidia_smi,
                    "--query-gpu=compute_cap",
                    "--format=csv,noheader",
                ],
                stdout=subprocess.PIPE,
                stderr=subprocess.DEVNULL,
            )
            .stdout.decode("utf-8")
            .strip()
        )

        gpu_ccs = []
        for c in compute_cap.split("\n"):
            c_ = c.strip()
            if len(c_) > 0:
                gpu_ccs.append(float(c_))

        if len(gpu_ccs) > 0:
            # Use the lowest compute capability among multiple GPUs
            config["gpu_compute_capability"] = str(int(min(gpu_ccs) * 10))
        else:
            config["gpu_compute_capability"] = "0"

    if config["NVCC"] == "":
        config["use_cuda"] = False
        if not config["quiet"]:
            print("Info: nvcc cannot be found. CUDA support is disabled.")
    else:
        if config["DISABLE_CUDA"]:
            config["use_cuda"] = False
            if not config["quiet"]:
                print(
                    "Info: nvcc found, but CUDA support is disabled in the configuration."
                )
        else:
            config["use_cuda"] = True
            if not config["quiet"]:
                print("Info: nvcc found, CUDA support is enabled.")
                print(f"NVCC: '{config['NVCC']}'")

    return config["NVCC"]


def find_CC():
    if config["COMPILER"] == "clang":
        config["CC"] = find_executable("clang")

    if config["COMPILER"] == "gcc":
        config["CC"] = find_executable("gcc")

    if config["COMPILER"] == "icx":
        config["CC"] = find_executable("icx")

    print(f"CC: '{config['CC']}'")

    if config["CC"] == "":
        print("Critical: C compiler cannot be found")

    return config["CC"]


def find_CXX():
    if config["COMPILER"] == "clang":
        config["CXX"] = find_executable("clang++")

    if config["COMPILER"] == "gcc":
        config["CXX"] = find_executable("g++")

    if config["COMPILER"] == "icx":
        config["CXX"] = find_executable("icpx")

    print(f"CXX: '{config['CXX']}'")

    if config["CXX"] == "":
        print("Critical: C++ compiler cannot be found")

    return config["CXX"]


def cpp_compiler_sanity_check():
    if config["dry_run"]:
        return True

    os.makedirs(config["tmp_dir"], exist_ok=True)
    hello_world_cpp = os.path.join(config["tmp_dir"], "hello_world.cpp")
    with open(hello_world_cpp, "w", newline="", encoding="utf-8") as f:
        f.write("#include <iostream>\n")
        f.write('int main() { std::cout << "Hello World!" << std::endl; return 0; }\n')

    output = subprocess.run(
        [
            config["CXX"],
            "-o",
            os.path.join(config["tmp_dir"], "hello_world"),
            hello_world_cpp,
        ],
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
    )
    return output.returncode == 0


def check_clang_selected_gcc():
    """
    Fix a known issue with clang on Ubuntu after installing cuda.
    """
    if cpp_compiler_sanity_check():
        return

    if config["COMPILER"] != "clang" or linux_distro() != "ubuntu":
        return

    output = subprocess.run(
        ["clang", "-v"], stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=True
    ).stdout.decode("utf-8")
    output_lines = output.split("\n")
    selected_gcc_version = ""
    for line in output_lines:
        l = line.strip()
        if l.startswith("Selected GCC installation"):
            selected_gcc_version = l.split("/")[-1]
            break
    print(f"Clang selected GCC version: {selected_gcc_version}")

    if config["dry_run"]:
        return

    if not is_package_installed(f"gcc-{selected_gcc_version}"):
        print("Installing Clang selected gcc version...")
        subprocess.run(
            ["sudo", "apt", "install", "-qq", "-y", f"gcc-{selected_gcc_version}"],
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
            check=True,
        )

    if not is_package_installed(f"g++-{selected_gcc_version}"):
        print("Installing Clang selected g++ version...")
        subprocess.run(
            ["sudo", "apt", "install", "-qq", "-y", f"g++-{selected_gcc_version}"],
            stdout=subprocess.DEVNULL if config["quiet"] else None,
            stderr=subprocess.DEVNULL if config["quiet"] else None,
            check=True,
        )


def create_version_file(data_dir, version):
    if config["dry_run"]:
        return

    with open(os.path.join(data_dir, version), "w") as f:
        f.write(f"{version}\n")


def check_third_parties(use_cuda=False):
    print("Checking third party libraries...")
    if config["dry_run"]:
        return

    nlohmann_dir = os.path.join(config["ext_dir"], "nlohmann")
    nlohmann_version_file = os.path.join(nlohmann_dir, config["NLOHMANN_JSON_VERSION"])
    if not os.path.exists(nlohmann_version_file):
        os.makedirs(nlohmann_dir, exist_ok=True)
        subprocess.run(
            [
                "curl",
                "-fsSL",
                f"https://github.com/nlohmann/json/releases/download/v{config['NLOHMANN_JSON_VERSION']}/json.hpp",
                "--output",
                os.path.join(nlohmann_dir, "json.hpp"),
            ],
            shell=False,
            check=True,
        )
        create_version_file(nlohmann_dir, config["NLOHMANN_JSON_VERSION"])
    print("nlohmann json installed")

    eigen_dir = os.path.join(config["ext_dir"], "eigen")
    eigen_version_file = os.path.join(eigen_dir, config["EIGEN_VERSION"])
    if not os.path.exists(eigen_version_file):
        os.makedirs(config["tmp_dir"], exist_ok=True)
        downloaded_file_path = os.path.join(
            config["tmp_dir"], f"eigen-{config['EIGEN_VERSION']}.tar.gz"
        )
        subprocess.run(
            [
                "curl",
                "-fsSL",
                f"https://gitlab.com/libeigen/eigen/-/archive/{config['EIGEN_VERSION']}/eigen-{config['EIGEN_VERSION']}.tar.gz",
                "--output",
                downloaded_file_path,
            ],
            shell=False,
            check=True,
        )
        subprocess.run(
            ["tar", "xzf", downloaded_file_path, "-C", config["ext_dir"]],
            shell=False,
            check=True,
        )
        subprocess.run(
            [
                "mv",
                os.path.join(config["ext_dir"], f"eigen-{config['EIGEN_VERSION']}"),
                eigen_dir,
            ],
            shell=False,
            check=True,
        )
        subprocess.run(["rm", downloaded_file_path], shell=False, check=True)
        create_version_file(eigen_dir, config["EIGEN_VERSION"])
    print("eigen installed")

    libxc_dir = os.path.join(config["ext_dir"], "libxc")
    libxc_version_file = os.path.join(libxc_dir, config["LIBXC_VERSION"])
    if not os.path.exists(libxc_version_file):
        os.makedirs(config["tmp_dir"], exist_ok=True)
        downloaded_file_path = os.path.join(
            config["tmp_dir"], f"libxc-{config['LIBXC_VERSION']}.tar.gz"
        )
        # The package downloaded from gitlab doesn't contain the configure script
        # subprocess.run(["curl", "-fsSL", f"https://gitlab.com/libxc/libxc/-/archive/{config['LIBXC_VERSION']}/libxc-{config['LIBXC_VERSION']}.tar.gz", "--output", downloaded_file_path], shell=False, check=True)
        subprocess.run(
            [
                "curl",
                "-fsSL",
                f"http://www.tddft.org/programs/libxc/down.php?file={config['LIBXC_VERSION']}/libxc-{config['LIBXC_VERSION']}.tar.gz",
                "--output",
                downloaded_file_path,
            ],
            shell=False,
            check=True,
        )
        subprocess.run(
            ["tar", "xzf", downloaded_file_path, "-C", config["tmp_dir"]],
            shell=False,
            check=True,
        )

        libxc_src_dir = os.path.join(
            config["tmp_dir"], f"libxc-{config['LIBXC_VERSION']}"
        )
        os.makedirs(libxc_dir, exist_ok=True)

        # The gitlab version requires running autoreconf
        # subprocess.run(["autoreconf", "-i"], cwd=libxc_src_dir, shell=False, check=True)

        if use_cuda:
            subprocess.run(
                [
                    f'CC="{config["NVCC"]} -x cu -ccbin clang --allow-unsupported-compiler" CFLAGS="--generate-code=arch=compute_{config["gpu_compute_capability"]},code=[compute_{config["gpu_compute_capability"]},sm_{config["gpu_compute_capability"]}] -O3 --std=c++14 --compiler-options -Wall,-Wfatal-errors,-Wno-unused-variable,-Wno-unused-but-set-variable" CCLD="/usr/local/cuda/bin/nvcc -ccbin clang --allow-unsupported-compiler" ./configure --enable-cuda --prefix={libxc_dir}'
                ],
                cwd=libxc_src_dir,
                shell=True,
                check=True,
            )
            subprocess.run(
                ["make", "-j", f"{os.cpu_count()}"],
                cwd=libxc_src_dir,
                shell=False,
                check=True,
            )
        else:
            subprocess.run(
                [
                    f"{os.path.join(libxc_src_dir, 'configure')}",
                    f"--prefix={libxc_dir}",
                ],
                cwd=libxc_src_dir,
                shell=False,
                check=True,
            )
            subprocess.run(
                ["make", "-j", f"{os.cpu_count()}"],
                cwd=libxc_src_dir,
                shell=False,
                check=True,
            )

        subprocess.run(["make", "install"], cwd=libxc_src_dir, shell=False, check=True)

        subprocess.run(["rm", downloaded_file_path], shell=False, check=True)
        subprocess.run(["rm", "-rf", libxc_src_dir], shell=False, check=True)
        create_version_file(libxc_dir, config["LIBXC_VERSION"])

    if os.path.exists(os.path.join(libxc_dir, "lib", "libxc.a")):
        config["STATIC_LIBS"].append(os.path.join(libxc_dir, "lib", "libxc.a"))
    elif os.path.exists(os.path.join(libxc_dir, "lib64", "libxc.a")):
        config["STATIC_LIBS"].append(os.path.join(libxc_dir, "lib64", "libxc.a"))
    else:
        raise RuntimeError("libxc static library not found")

    print("libxc installed")

    sto_3g_file = os.path.join(config["root_dir"], "basis-set", "sto-3g.json")
    if not os.path.exists(sto_3g_file):
        subprocess.run(
            [
                "curl",
                "-fsSL",
                "https://www.basissetexchange.org/api/basis/sto-3g/format/json/",
                "--output",
                sto_3g_file,
            ],
            shell=False,
            check=True,
        )
    print("sto-3g downloaded")

    return 0


def remove_installed_third_parties():
    import shutil

    nlohmann_dir = os.path.join(config["ext_dir"], "nlohmann")
    eigen_dir = os.path.join(config["ext_dir"], "eigen")
    libxc_dir = os.path.join(config["ext_dir"], "libxc")
    sto_3g_file = os.path.join(config["root_dir"], "basis-set", "sto-3g.json")

    if os.path.exists(nlohmann_dir):
        shutil.rmtree(nlohmann_dir)
    if os.path.exists(eigen_dir):
        shutil.rmtree(eigen_dir)
    if os.path.exists(libxc_dir):
        shutil.rmtree(libxc_dir)
    if os.path.exists(sto_3g_file):
        os.remove(sto_3g_file)


def setup_toolchain():
    install_build_tools()
    find_compilers()
    check_third_parties(use_cuda=False)


if __name__ == "__main__":
    setup_toolchain()
