#!/bin/bash

echo "Setting up ccache..."

export PATH="/usr/lib/ccache/:${PATH}"
export CCACHE_BASEDIR="${PWD}"
export CCACHE_DIR="${PWD}/ccache"
export CCACHE_CPP2="yes"

mkdir -p ccache
