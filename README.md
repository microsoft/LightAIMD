# LightAIMD

| - | Ubuntu 22.04 |
|---|---|
|Build|![Build status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|
|Sanity Test|![Test status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|

LightAIMD is a lightweight AIMD (*ab initio* molecular dynamics) simulation program for simulating aperiodic molecular systems, such as biomolecules.

## Getting started
You can use the `scripts/build.py` script to set up the development environment and build LightAIMD. This project provides a meta build system that automatically detects the code dependencies, generates the [Ninja](https://ninja-build.org/) build scripts, and builds the project. The meta build system should work for most modern Ubuntu systems (tested on Ubuntu 18.04, 20.04, and 22.04). Please adapt the scripts for other Linux distributions.

To build LightAIMD, simply run (python3 is required):
```shell
python3 scripts/build.py --build --release
```

To build the debug version:
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
The default compiler is clang. To use the icx/icpx compiler, you need to install the [Intel® oneAPI Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html) and configure the local environment variables using the `setvars.sh` script, which can be found in the installation directory, for example:
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
