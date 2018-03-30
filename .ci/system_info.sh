#!/bin/sh

echo "-------------------- BEGIN SYSTEM INFORMATION --------------------"
echo $0
pwd
ls
hostname
uname -a
lsb_release -a
env
cat /etc/apt/sources.list
ls /etc/apt/sources.list.d
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
echo "--------------------  END SYSTEM INFORMATION  --------------------"
