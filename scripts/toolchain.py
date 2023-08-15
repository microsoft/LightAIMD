#!/usr/bin/env python3
import os
import sys
import subprocess
from config import *

__all__ = ['setup_toolchain', 'remove_installed_third_parties']


def install_build_tools():
    print("Installing build tools...")
    subprocess.run(["sudo", "apt", "update", "-qq"], check=True)
    subprocess.run(["sudo", "apt", "install", "-qq", "-y",
                   "build-essential", "gfortran", "clang", "ninja-build"], check=True)
    print("Build tools installed")


def find_compilers():
    find_CC()
    find_CXX()
    find_nvcc()


def find_nvcc():
    config['NVCC'] = subprocess.run(['which', 'nvcc'], stdout=subprocess.PIPE, stderr=subprocess.DEVNULL).stdout.decode('utf-8').strip()
    print(f"NVCC: '{config['NVCC']}'")

    nvidia_smi = subprocess.run(['which', 'nvidia-smi'], stdout=subprocess.PIPE,
                                stderr=subprocess.DEVNULL).stdout.decode('utf-8').strip()

    if nvidia_smi != '':
        compute_cap = subprocess.run([nvidia_smi, '--query-gpu=compute_cap', '--format=csv,noheader'],
                                     stdout=subprocess.PIPE, stderr=subprocess.DEVNULL).stdout.decode('utf-8').strip()

        gpu_ccs = []
        for c in compute_cap.split('\n'):
            c_ = c.strip()
            if len(c_) > 0:
                gpu_ccs.append(float(c_))

        if len(gpu_ccs) > 0:
            # Use the lowest compute capability among multiple GPUs
            config['gpu_compute_capability'] = str(int(min(gpu_ccs)*10))
        else:
            config['gpu_compute_capability'] = '0'

    if config['NVCC'] == '':
        config['USE_CUDA'] = 'NO'
        print('Warning: nvcc cannot be found, CUDA support is disabled. In order to use CUDA, please set the NVCC environment variable to the path of the nvcc.')
    else:
        config['USE_CUDA'] = 'YES'
        print('Info: nvcc found, CUDA support is enabled')

    return config['NVCC']


def find_CC():
    config['CC'] = subprocess.run(['which', 'clang'], stdout=subprocess.PIPE,
                                  stderr=subprocess.DEVNULL).stdout.decode('utf-8').strip()
    print(f"CC: '{config['CC']}'")

    if config['CC'] == '':
        print('Critical: C compiler cannot be found')

    return config['CC']


def find_CXX():
    config['CXX'] = subprocess.run(['which', 'clang++'], stdout=subprocess.PIPE,
                                   stderr=subprocess.DEVNULL).stdout.decode('utf-8').strip()
    print(f"CXX: '{config['CXX']}'")

    if config['CXX'] == '':
        print('Critical: C++ compiler cannot be found')

    return config['CXX']


def create_version_file(data_dir, version):
    with open(os.path.join(data_dir, version), 'w') as f:
        f.write(f"{version}\n")


def check_third_parties(use_cuda=False):
    nlohmann_dir = os.path.join(config['ext_dir'], 'nlohmann')
    nlohmann_version_file = os.path.join(
        nlohmann_dir, config['NLOHMANN_JSON_VERSION'])
    if not os.path.exists(nlohmann_version_file):
        os.makedirs(nlohmann_dir, exist_ok=True)
        subprocess.run(["curl", "-fsSL", f"https://github.com/nlohmann/json/releases/download/v{config['NLOHMANN_JSON_VERSION']}/json.hpp", "--output", os.path.join(
            nlohmann_dir, "json.hpp")], shell=False, check=True)
        create_version_file(nlohmann_dir, config['NLOHMANN_JSON_VERSION'])
    print('nlohmann json installed')

    eigen_dir = os.path.join(config['ext_dir'], 'eigen')
    eigen_version_file = os.path.join(eigen_dir, config['EIGEN_VERSION'])
    if not os.path.exists(eigen_version_file):
        os.makedirs(config['tmp_dir'], exist_ok=True)
        downloaded_file_path = os.path.join(
            config['tmp_dir'], f"eigen-{config['EIGEN_VERSION']}.tar.gz")
        subprocess.run(
            ["curl", "-fsSL", f"https://gitlab.com/libeigen/eigen/-/archive/{config['EIGEN_VERSION']}/eigen-{config['EIGEN_VERSION']}.tar.gz", "--output", downloaded_file_path], shell=False, check=True)
        subprocess.run(["tar", "xzf", downloaded_file_path, "-C",
                       config['ext_dir']], shell=False, check=True)
        subprocess.run(["mv", os.path.join(
            config['ext_dir'], f"eigen-{config['EIGEN_VERSION']}"), eigen_dir], shell=False, check=True)
        subprocess.run(["rm", downloaded_file_path], shell=False, check=True)
        create_version_file(eigen_dir, config['EIGEN_VERSION'])
    print('eigen installed')

    libxc_dir = os.path.join(config['ext_dir'], 'libxc')
    libxc_version_file = os.path.join(libxc_dir, config['LIBXC_VERSION'])
    if not os.path.exists(libxc_version_file):
        os.makedirs(config['tmp_dir'], exist_ok=True)
        downloaded_file_path = os.path.join(
            config['tmp_dir'], f"libxc-{config['LIBXC_VERSION']}.tar.gz")
        # The package downloaded from gitlab doesn't contain the configure script
        # subprocess.run(["curl", "-fsSL", f"https://gitlab.com/libxc/libxc/-/archive/{config['LIBXC_VERSION']}/libxc-{config['LIBXC_VERSION']}.tar.gz", "--output", downloaded_file_path], shell=False, check=True)
        subprocess.run(
            ["curl", "-fsSL", f"http://www.tddft.org/programs/libxc/down.php?file={config['LIBXC_VERSION']}/libxc-{config['LIBXC_VERSION']}.tar.gz", "--output", downloaded_file_path], shell=False, check=True)
        subprocess.run(["tar", "xzf", downloaded_file_path, "-C",
                       config['tmp_dir']], shell=False, check=True)

        libxc_src_dir = os.path.join(
            config['tmp_dir'], f"libxc-{config['LIBXC_VERSION']}")
        os.makedirs(libxc_dir, exist_ok=True)

        # The gitlab version requires running autoreconf
        # subprocess.run(["autoreconf", "-i"], cwd=libxc_src_dir, shell=False, check=True)

        if use_cuda:
            subprocess.run([f'CC="{config["NVCC"]} -x cu -ccbin clang --allow-unsupported-compiler" CFLAGS="--generate-code=arch=compute_{config["gpu_compute_capability"]},code=[compute_{config["gpu_compute_capability"]},sm_{config["gpu_compute_capability"]}] -O3 --std=c++14 --compiler-options -Wall,-Wfatal-errors,-Wno-unused-variable,-Wno-unused-but-set-variable" CCLD="/usr/local/cuda/bin/nvcc -ccbin clang --allow-unsupported-compiler" ./configure --enable-cuda --prefix={libxc_dir}'], cwd=libxc_src_dir, shell=True, check=True)
            subprocess.run(
                ["make", "-j", f"{os.cpu_count()}"], cwd=libxc_src_dir, shell=False, check=True)
        else:
            subprocess.run([f"{os.path.join(libxc_src_dir, 'configure')}",
                           f"--prefix={libxc_dir}"], cwd=libxc_src_dir, shell=False, check=True)
            subprocess.run(
                ["make", "-j", f"{os.cpu_count()}"], cwd=libxc_src_dir, shell=False, check=True)

        subprocess.run(["make", "install"], cwd=libxc_src_dir,
                       shell=False, check=True)

        subprocess.run(["rm", downloaded_file_path], shell=False, check=True)
        subprocess.run(["rm", "-rf", libxc_src_dir], shell=False, check=True)
        create_version_file(libxc_dir, config['LIBXC_VERSION'])
    print('libxc installed')

    sto_3g_file = os.path.join(config['root_dir'], 'basis-set', 'sto-3g.json')
    if not os.path.exists(sto_3g_file):
        subprocess.run(["curl", "-fsSL", "https://www.basissetexchange.org/api/basis/sto-3g/format/json/",
                       "--output", sto_3g_file], shell=False, check=True)
    print('sto-3g downloaded')

    return 0


def remove_installed_third_parties():
    import shutil
    nlohmann_dir = os.path.join(config['ext_dir'], 'nlohmann')
    eigen_dir = os.path.join(config['ext_dir'], 'eigen')
    libxc_dir = os.path.join(config['ext_dir'], 'libxc')
    sto_3g_file = os.path.join(config['root_dir'], 'basis-set', 'sto-3g.json')

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
    print_config()
