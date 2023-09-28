# LightAIMD

| - | Ubuntu 22.04 |
|---|---|
|Build|![Build status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|
|Sanity Test|![Test status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|

LightAIMD is a lightweight AIMD (*ab initio* molecular dynamics) simulation program for simulating aperiodic molecular systems, such as biomolecules.

## Getting started
You can use the `scripts/build.py` script (python3 is required) to set up the development environment and build LightAIMD. This project provides a meta build system that automatically detects the code dependencies, generates the [Ninja](https://ninja-build.org) build scripts, and builds the project. The meta build system should work for most modern Linux systems.

To install the build tools, run the following command if a supported package manager, `apt`, `dnf`, `pacman`, or `zypper`, is available on your system:
```shell
python3 scripts/build.py --install-build-tools
```

If a supported package manager cannot be found, the build script will print the missing required packages and you need to install them manually. The following packages are required:
- python3 (for running the build script)
- git (for cloning the source code)
- [curl](https://curl.se/download.html) (for downloading the external dependencies)
- C and C++ compiler (GCC, Clang, or Intel® C/C++ compiler)
- gfortran (for building libxc)
- [GNU AutoTools](https://en.wikipedia.org/wiki/GNU_Autotools) (for building libxc)
- [Ninja](https://ninja-build.org) Build system
- [CUDA Toolkit](https://developer.nvidia.com/cuda-downloads) (optional, for building the CUDA-enabled version of LightAIMD)

To build LightAIMD, simply run:
```shell
python3 scripts/build.py --build --release
```

To build the debug version, run:
```shell
python3 scripts/build.py --build --debug
```

You can also build the release version and the debug version at the same time:
```shell
python3 scripts/build.py --build --release --debug
```

The supported compilers include Clang, GCC, and Intel® C/C++ compiler (icx/icpx). You can specify the compiler by using "--compiler" option, with the following choices: "clang", "gcc", and "icx". For example, to use gcc:
```shell
python3 scripts/build.py --build --release --compiler gcc
```
The default compiler is gcc. To use the icx/icpx compiler, you need to install the [Intel® oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html) and configure the local environment variables using the `setvars.sh` script, which can be found in the installation directory, for example:
```shell
source /opt/intel/oneapi/setvars.sh
```

If the Nvidia CUDA Compiler `nvcc` is detected, the build script will compile the CUDA-enabled version of LightAIMD. To explicitly disable CUDA support, you can use the `--disable-cuda` option:
```shell
python3 scripts/build.py --build --release --disable-cuda
```

### Sanity tests
After building LightAIMD, you can run the sanity tests:
```shell
python3 scripts/build.py --sanity-test --release
```

You can run the sanity tests for both the release version and the debug version if you have built both versions:
```shell
python3 scripts/build.py --sanity-test --release --debug
```

### Run your first simulation
You can run an HF (Hartree-Fock) based simulation:
```shell
./build/release/bin/lightaimd --hf --bomd --mol sample/h2o.xyz
```
or you can run a DFT (Density Functional Theory) based simulation:
```shell
./build/release/bin/lightaimd --dft --bomd --mol sample/h2o.xyz
```

Here, *--bomd* stands for Born-Oppenheimer Molecular Dynamics.

## Features

LightAIMD currently supports Hartree-Fock and Density Functional Theory based quantum chemistry calculations. Given a molecular structure, LightAIMD can calculate single point energy, single point forces (electronic forces on the nuclei), or perform Born-Oppenheimer molecular dynamics simulation.

## Design philosophy

- Minimalist yet generic
  - Supports all the basis sets on [BSE](https://www.basissetexchange.org/) (Basis Set Exchange)
  - Supports the following types of functionals provided by [Libxc](https://tddft.org/programs/libxc/): LDA, GGA, Hybrid GGA, MGGA, Hybrid MGGA
- As self-contained as possible by minimizing external dependency

## Contributing

Please read the [development guide](docs/dev-guide.md) and the [code of conduct](CODE_OF_CONDUCT.md) for contributing code.

Follow these [instructions](SECURITY.md) for reporting security issues.

## License

Copyright (c) Microsoft Corporation. All rights reserved.

Licensed under the [MIT](LICENSE.txt) license.

## Disclaimer

LightAIMD is currently a research project. It is not an officially supported Microsoft product.

## Acknowledgements

The repo doesn't contain 3rd party code. It links to the following external libraries:
- [Eigen](https://eigen.tuxfamily.org)
- [Libxc](https://www.tddft.org/programs/libxc/)
- [Nlohmann/json](https://github.com/nlohmann/json)

To understand the theory behind LightAIMD, you may refer to this [tutorial](https://www.binshao.info/download/tutorials/CQC101.pdf).
