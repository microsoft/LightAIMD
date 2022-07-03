#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
ROOT_DIR=$(dirname $SCRIPT_DIR)
PROCESSOR_COUNT=$(grep -c processor /proc/cpuinfo)

NLOHMANN_JSON_VERSION=3.10.5
EIGEN_VERSION=3.4.0
LIBXC_VERSION=5.2.3

set -ex

sudo apt-get update
sudo apt-get install -y \
     build-essential \
     gfortran \
     clang

if [ ! -e $ROOT_DIR/ext/nlohmann ]; then
  mkdir -p $ROOT_DIR/ext/nlohmann
  wget https://github.com/nlohmann/json/releases/download/v$NLOHMANN_JSON_VERSION/json.hpp \
    -O $ROOT_DIR/ext/nlohmann/json.hpp
fi

if [ ! -e $ROOT_DIR/ext/eigen ]; then
  wget https://gitlab.com/libeigen/eigen/-/archive/$EIGEN_VERSION/eigen-$EIGEN_VERSION.tar.gz \
       -O /tmp/eigen-$EIGEN_VERSION.tar.gz
  tar xzf /tmp/eigen-$EIGEN_VERSION.tar.gz -C $ROOT_DIR/ext
  mv $ROOT_DIR/ext/eigen-$EIGEN_VERSION $ROOT_DIR/ext/eigen
  rm /tmp/eigen-$EIGEN_VERSION.tar.gz
fi

if [ ! -e $ROOT_DIR/ext/libxc ]; then
  wget http://www.tddft.org/programs/libxc/down.php?file=$LIBXC_VERSION/libxc-$LIBXC_VERSION.tar.gz \
       -O /tmp/libxc-$LIBXC_VERSION.tar.gz
  tar xzf /tmp/libxc-$LIBXC_VERSION.tar.gz -C /tmp
  cd /tmp/libxc-$LIBXC_VERSION
  install_dir=$ROOT_DIR/ext/libxc
  mkdir -p $install_dir
  ./configure --prefix=$install_dir
  make -j $PROCESSOR_COUNT && make -j $PROCESSOR_COUNT check
  make install
  cd $ROOT_DIR
  rm -rf /tmp/libxc-$LIBXC_VERSION.tar.gz /tmp/libxc-$LIBXC_VERSION
fi

wget https://www.basissetexchange.org/api/basis/sto-3g/format/json/ -O basis-set/sto-3g.json
