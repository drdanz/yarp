#!/bin/bash

echo "Building examples using YARP from build tree"
export EXAMPLE_SOURCE_DIR="${YARP_SOURCE_DIR}/example/os"
export EXAMPLE_BINARY_DIR="${EXAMPLE_SOURCE_DIR}/build-bt"
export YARP_DIR="${YARP_BINARY_DIR}"
mkdir -p ${EXAMPLE_BINARY_DIR}
(cd ${EXAMPLE_BINARY_DIR}; cmake -G"${YARP_CMAKE_GENERATOR}" \
                                 -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
                                 -DYARP_DIR=${YARP_DIR} \
                                 ${EXAMPLE_SOURCE_DIR})
(cd ${EXAMPLE_BINARY_DIR}; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})


echo "Building examples using YARP from install tree"
export EXAMPLE_SOURCE_DIR="${YARP_SOURCE_DIR}/example/os"
export EXAMPLE_BINARY_DIR="${EXAMPLE_SOURCE_DIR}/build-it"
export YARP_DIR="${YARP_INSTALL_PREFIX}/lib/cmake/YARP"
mkdir -p ${EXAMPLE_BINARY_DIR}
(cd ${EXAMPLE_BINARY_DIR}; cmake -G"${YARP_CMAKE_GENERATOR}" \
                                 -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
                                 -DYARP_DIR=${YARP_DIR} \
                                 ${EXAMPLE_SOURCE_DIR})
(cd ${EXAMPLE_BINARY_DIR}; cmake --build . --config ${YARP_CMAKE_BUILD_TYPE})
