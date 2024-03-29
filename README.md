# LightAIMD

| - | Ubuntu 22.04 |
|---|---|
|Build|![Build status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|
|Sanity Test|![Test status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|

LightAIMD is a lightweight AIMD (*ab initio* molecular dynamics) simulation program for simulating aperiodic molecular systems, such as biomolecules.

## Features

LightAIMD supports Hartree-Fock and Density Functional Theory based quantum chemistry calculations. Given a 3D molecular structure, LightAIMD can calculate single point energy, single point forces (electronic forces acting on the nuclei), or perform Born-Oppenheimer molecular dynamics simulation.

## Getting started
You can use the `scripts/build.py` script to set up the development environment and build LightAIMD. This project provides a meta build system that automatically detects the code dependencies, generates the [Ninja](https://ninja-build.org) build scripts, and builds the project. The meta build system should work for most modern Linux systems.

To install the build tools, run the following command (`python3` is required) if a supported package manager, `apt`, `dnf`, `pacman`, or `zypper`, is available on your system:
```shell
python3 scripts/build.py --install-build-tools
```

If the build script cannot locate a supported package manager, it will print the required packages that are missing and you need to install them manually. The following packages are required:
- python3 (for running the build script)
- git (for cloning the source code)
- [curl](https://curl.se/download.html) (for downloading the external libraries)
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

The supported compilers include Clang, GCC, and Intel® C compiler (icx). You can specify the compiler by using "--compiler" option, with the following choices: "clang", "gcc", and "icx". For example, to use clang:
```shell
python3 scripts/build.py --build --release --compiler clang
```
The default compiler is gcc. To use the icx compiler, you need to install the [Intel® oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html) and configure the local environment variables using the `setvars.sh` script, which can be found in the installation directory, for example:
```shell
source /opt/intel/oneapi/setvars.sh
```

If Intel® oneMKL, which is included in the Intel® oneAPI Base Toolkit, is installed and the local environment is configured with the above command, you can link to the Intel® oneMKL library instead of `liblapacke` by using the `--use-mkl` option:
```shell
python3 scripts/build.py --build --release --use-mkl # use the default compiler gcc
```

If you want to use the Intel® oneMKL library with the icx compiler, run the following command:
```shell
python3 scripts/build.py --build --release --use-mkl --compiler icx # use icx compiler
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

#### Single point energy calculation
You can run a Hartree-Fock (HF) based single point energy calculation:
```shell
./build/release/bin/lightaimd --hf --mol samples/h2o.xyz
```
or you can run a Density Functional Theory (DFT) based single point energy calculation:
```shell
./build/release/bin/lightaimd --dft --mol samples/h2o.xyz
```

#### Single point force calculation
You can run a HF based single point force calculation:
```shell
./build/release/bin/lightaimd --hf --force --mol samples/h2o.xyz
```
or you can run a DFT based single point force calculation:
```shell
./build/release/bin/lightaimd --dft --force --mol samples/h2o.xyz
```

#### *Ab Initio* Molecular Dynamics (AIMD) simulation
You can run an HF (Hartree-Fock) based simulation:
```shell
./build/release/bin/lightaimd --hf --bomd --mol samples/h2o.xyz
```
or you can run a DFT (Density Functional Theory) based simulation:
```shell
./build/release/bin/lightaimd --dft --bomd --mol samples/h2o.xyz
```

Here, *--bomd* stands for Born-Oppenheimer (*Ab Initio*) Molecular Dynamics.

## Design philosophy

- Minimalist yet generic
  - Supports all the basis sets on [BSE](https://www.basissetexchange.org/) (Basis Set Exchange)
  - Supports the following types of functionals provided by [Libxc](https://tddft.org/programs/libxc/): LDA, GGA, Hybrid GGA, MGGA, and Hybrid MGGA
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
- [Libxc](https://www.tddft.org/programs/libxc/)
- [Lapacke](https://www.netlib.org/lapack/lapacke.html)

To understand the theory behind LightAIMD, you may refer to this [tutorial](https://www.binshao.info/download/tutorials/CQC101.pdf).
