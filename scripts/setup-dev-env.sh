#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
ROOT_DIR=$(dirname $SCRIPT_DIR)
PROCESSOR_COUNT=$(grep -c processor /proc/cpuinfo)

set -ex

sudo apt-get update
sudo apt-get install -y \
     build-essential \
     gfortran \
     clang

if [ ! -e $ROOT_DIR/ext/nlohmann ]; then
  mkdir -p $ROOT_DIR/ext/nlohmann
  wget https://github.com/nlohmann/json/releases/download/v3.10.5/json.hpp \
    -O $ROOT_DIR/ext/nlohmann/json.hpp
fi

if [ ! -e $ROOT_DIR/ext/eigen-3.4.0 ]; then
  wget https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz \
       -O /tmp/eigen-3.4.0.tar.gz
  tar xzf /tmp/eigen-3.4.0.tar.gz -C $ROOT_DIR/ext
  rm /tmp/eigen-3.4.0.tar.gz
fi

if [ ! -e $ROOT_DIR/ext/libxc-5.2.2/libxc ]; then
  wget http://www.tddft.org/programs/libxc/down.php?file=5.2.2/libxc-5.2.2.tar.gz \
       -O /tmp/libxc-5.2.2.tar.gz
  tar xzf /tmp/libxc-5.2.2.tar.gz -C /tmp
  cd /tmp/libxc-5.2.2
  install_dir=$ROOT_DIR/ext/libxc-5.2.2/libxc
  mkdir -p $install_dir
  ./configure --prefix=$install_dir
  make -j $PROCESSOR_COUNT && make -j $PROCESSOR_COUNT check
  make install
  cd $ROOT_DIR
  rm -rf /tmp/libxc-5.2.2.tar.gz /tmp/libxc-5.2.2
fi

wget https://www.basissetexchange.org/api/basis/sto-3g/format/json/ -O basis-set/sto-3g.json
