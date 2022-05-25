# LightAIMD

| - | Ubuntu 20.04 |
|---|---|
|Build|![Build status badge](https://msai.visualstudio.com/LightAIMD/_apis/build/status/LightAIMD-CI)|

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

### Tests
```shell
bash tests/compare-with-ref-energies-forces.sh
```

### Run your first simulation
You can run an HF (Hartree-Fock) based simulation:
```shell
./hf.exe --bomd --mol sample/h2o.xyz
```
or you can run a DFT (Density Functional Theory) based simulation:
```shell
./dft.exe --bomd --mol sample/h2o.xyz
```

Here, *--bomd* stands for Born-Oppenheimer Molecular Dynamics.

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

Besides the above libraries that LightAIMD communicates with, we've learned a lot from the following projects. Thank you!
- [PySCF](https://github.com/pyscf/pyscf)
- [McMurchie-Davidson](https://github.com/jjgoings/McMurchie-Davidson)
