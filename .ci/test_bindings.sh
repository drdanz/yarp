#!/bin/bash

if (( $# != 1 )); then
    echo "Usage: $0 [language]"
    exit 1
fi
language=$(echo "$1" | tr '[:lower:]' '[:upper:]')


export YARP_BINDINGS_CMAKE_OPTIONS="-DYARP_COMPILE_BINDINGS=ON -DCREATE_${language}=ON"


################################################################################
echo "Building ${language} bindings - Out of source build (build tree)"
export BINDINGS_SOURCE_DIR="${CI_PROJECT_DIR}/bindings"
export BINDINGS_BINARY_DIR="${BINDINGS_SOURCE_DIR}/build-${language}"
export YARP_DIR="${YARP_BINARY_DIR}"

mkdir -p ${BINDINGS_BINARY_DIR}
(cd ${BINDINGS_BINARY_DIR}; cmake -G"${YARP_CMAKE_GENERATOR}" \
                                  -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
                                  -DYARP_DIR=${YARP_DIR} \
                                  ${YARP_BINDINGS_CMAKE_OPTIONS} \
                                  ${BINDINGS_SOURCE_DIR})
(cd ${BINDINGS_BINARY_DIR}; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})


################################################################################
echo "Building ${language} bindings - Out of source build (install tree)"
export BINDINGS_SOURCE_DIR="${YARP_INSTALL_PREFIX}/share/yarp/bindings"
export BINDINGS_BINARY_DIR="${BINDINGS_SOURCE_DIR}/build-${language}"
export YARP_DIR=${YARP_INSTALL_DIR}

mkdir -p ${BINDINGS_BINARY_DIR}
(cd ${BINDINGS_BINARY_DIR}; cmake -G"${YARP_CMAKE_GENERATOR}" \
                                  -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
                                  -DYARP_DIR=${YARP_BINARY_DIR} \
                                  ${YARP_BINDINGS_CMAKE_OPTIONS} \
                                  ${BINDINGS_SOURCE_DIR})
(cd ${BINDINGS_BINARY_DIR}; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})


################################################################################
echo "Building ${language} bindings - Nested build"
unset BINDINGS_SOURCE_DIR
unset BINDINGS_BINARY_DIR
unset YARP_DIR

(cd ${YARP_BINARY_DIR}; cmake . ${YARP_BINDINGS_CMAKE_OPTIONS})
(cd ${YARP_BINARY_DIR}; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})
