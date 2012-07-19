#!/bin/bash

echo "Preparing package in tmp"

echo "  adding control file"

rm -rf tmp
mkdir -p tmp/DEBIAN/
cp control tmp/DEBIAN

echo "  adding library .a"

mkdir -p tmp/usr/lib
find ../lib -iname "*.a" -exec cp {} tmp/usr/lib \;

echo "  adding user header files .h"

mkdir -p tmp/usr/include/yarp/sig
find ../include/yarp/sig -iname "*.h" -exec cp {} tmp/usr/include/yarp/sig \;

#echo "  adding standard companion"

#mkdir -p tmp/usr/bin

#find ../bin -iname "yarp" -exec cp {} tmp/usr/bin \;

echo "  inventory:"

find tmp

echo "making package"

dpkg --build tmp libyarp-sig-dev.deb

echo "cleaning up"

rm -rf tmp
