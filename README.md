# LightAIMD

| - | Ubuntu 22.04 |
|---|---|
|Build|![Build status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|
|Sanity Test|![Test status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|

LightAIMD is a lightweight AIMD (*ab initio* molecular dynamics) simulation program for simulating aperiodic molecular systems, such as biomolecules.

## Getting started
You can use the *scripts/setup-dev-env.sh* script to set up the development environment. The script should work for most modern Ubuntu systems (tested on Ubuntu 18.04, 20.04, and 22.04). Please adapt the script for other Linux distributions.

```shell
bash scripts/setup-dev-env.sh
```

If it doesn't work, you can set up the environment manually by following these [instructions](docs/setup-dev-env.md).

### Compile LightAIMD
To build LightAIMD, simply run (don't omit the parentheses):
```shell
(cd src && make clean && make all)
```

To build the debug version:
```shell
(cd src && make clean && make debug)
```

### Sanity tests
After building LightAIMD, you can run the sanity tests:
```shell
bash tests/compare-with-ref-energies-forces.sh
```

### Run your first simulation
You can run an HF (Hartree-Fock) based simulation:
```shell
bin/lightaimd --hf --bomd --mol sample/h2o.xyz
```
or you can run a DFT (Density Functional Theory) based simulation:
```shell
bin/lightaimd --dft --bomd --mol sample/h2o.xyz
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

Besides the above libraries that LightAIMD communicates with, the following projects have greatly inspired the design of LightAIMD:
- [PySCF](https://github.com/pyscf/pyscf)
- [McMurchie-Davidson](https://github.com/jjgoings/McMurchie-Davidson)
