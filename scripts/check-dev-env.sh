#!/bin/bash

SCRIPT_DIR=$(dirname "$(readlink -f "$0")")
ROOT_DIR=$(dirname $SCRIPT_DIR)

set -e

if [ ! -d $ROOT_DIR/ext/nlohmann ]; then
    echo "ext/nlohmann does not exist, rerun scripts/setup-dev-env.sh"
    bash $SCRIPT_DIR/setup-dev-env.sh
fi

if [ ! -d $ROOT_DIR/ext/eigen ]; then
    echo "ext/eigen does not exist, rerun bash scripts/setup-dev-env.sh"
    bash $SCRIPT_DIR/setup-dev-env.sh
fi

if [ ! -d $ROOT_DIR/ext/libxc ]; then
    echo "ext/libxc does not exist, rerun bash scripts/setup-dev-env.sh"
    bash $SCRIPT_DIR/setup-dev-env.sh
fi

if [ ! -f $ROOT_DIR/basis-set/sto-3g.json ]; then
    echo "basis-set/sto-3g.json does not exist, rerun bash scripts/setup-dev-env.sh"
    bash $SCRIPT_DIR/setup-dev-env.sh
fi
