#!/bin/bash

. scripts/admin/generate-cmake-options.sh $(hostname) $(lsb_release -cs) continuous

export YARP_INSTALL_PREFIX="${PWD}/install"
export YARP_CMAKE_OPTIONS="${CMAKE_OPTIONS} -DCMAKE_INSTALL_PREFIX=${YARP_INSTALL_PREFIX}"
export YARP_CMAKE_OPTIONS="${YARP_CMAKE_OPTIONS} -DENABLE_yarpcar_h264:BOOL=ON"

# Print cmake build flags
echo "--------------------     BEGIN CMAKE FLAGS    --------------------"
echo "cmake -G"${YARP_CMAKE_GENERATOR}" \
            -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
            ${YARP_CMAKE_OPTIONS} \
            ${YARP_EXTRA_CMAKE_OPTIONS} \
            .." | sed 's/ -/ \\\n  -/g'
echo "--------------------      END CMAKE FLAGS     --------------------"

echo mkdir build
(cd build; cmake -G"${YARP_CMAKE_GENERATOR}" \
                 -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
                 ${YARP_CMAKE_OPTIONS} \
                 ${YARP_EXTRA_CMAKE_OPTIONS} \
                 ..)
