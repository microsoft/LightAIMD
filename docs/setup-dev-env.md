# Setup Development Environment
## Install Compilers
For example, on Ubuntu, run

```shell
sudo apt-get update
sudo apt-get install -y build-essential gfortran clang
```

## Download the external libraries

Suppose we are in the root directory of the repo.

## nlohmann/json
Download the latest [nlohmann/json](https://github.com/nlohmann/json/releases) and extract json.hpp to "ext/nlohmann/".

```shell
mkdir -p ext/nlohmann
wget https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp -O ext/nlohmann/json.hpp
```

## eigen
Download [eigen-3.4.0](https://gitlab.com/libeigen/eigen/-/releases) and extract eigen-3.4.0.tar.bz2 to "ext/eigen-3.4.0".

```shell
wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz -O ext/eigen-3.4.0.tar.gz
tar xzf ext/eigen-3.4.0.tar.gz -C ext
rm ext/eigen-3.4.0.tar.gz
```

## libxc
Download [libxc-5.2.0](https://www.tddft.org/programs/libxc/download/) and extract libxc-5.2.2.tar.gz to "ext/libxc-5.2.2".
Compile libxc (replace 16 to the number of CPU cores on your machine):

```shell
wget http://www.tddft.org/programs/libxc/down.php?file=5.2.2/libxc-5.2.2.tar.gz -O ext/libxc-5.2.2.tar.gz
tar xzf ext/libxc-5.2.2.tar.gz -C ext
rm ext/libxc-5.2.2.tar.gz
cd ext/libxc-5.2.2
mkdir libxc && ./configure --prefix=`pwd`/libxc
make -j 16
make -j 16 check
make install
```

## Basis-set

Download the basis sets you need, e.g., STO-3G, in JSON format from [Basis Set Exchange](https://www.basissetexchange.org/) and put them to "basis-set/".
