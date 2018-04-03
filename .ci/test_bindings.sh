#!/bin/bash

if (( $# != 1 )); then
    echo "Usage: $0 [language]"
fi

_lang=$(echo "$1" | tr '[:lower:]' '[:upper:]')
export YARP_BINDINGS_CMAKE_OPTIONS="-DYARP_COMPILE_BINDINGS=ON -DCREATE_${_lang}=ON"
echo "Building ${_lang} bindings"

echo "Nested build"
(cd build; cmake . ${YARP_BINDINGS_CMAKE_OPTIONS})
(cd build; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})

echo "Out of source build"
mkdir -p bindings/build
(cd bindings/build; cmake -G"${YARP_CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} -DYARP_DIR=${PWD}/../../build ${YARP_BINDINGS_CMAKE_OPTIONS} ..)
(cd bindings/build; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})
