#!/bin/bash

echo "-------------------- BEGIN SYSTEM INFORMATION --------------------"
set -o xtrace
pwd
ls
hostname
uname -a
lsb_release -a
env
cat /etc/apt/sources.list
ls /etc/apt/sources.list.d
update-alternatives --get-selections
# update-alternatives --query cc
# update-alternatives --query gcc
# update-alternatives --query clang
# update-alternatives --query cmake
which cmake
cmake --version
which $CC
$CC --version
which $CXX
$CXX --version
which ccache
ccache --version
ccache -s
ls -la /usr/lib/ccache
which swig3.0
swig3.0 -version
which javac
javac -version
set +o xtrace
echo "--------------------  END SYSTEM INFORMATION  --------------------"
