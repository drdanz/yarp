#!/bin/bash

# Prepare CMake options
. "${YARP_SOURCE_DIR}/scripts/admin/generate-cmake-options.sh" $(hostname) $(lsb_release -cs) continuous
export YARP_CMAKE_OPTIONS="${CMAKE_OPTIONS} -DCMAKE_INSTALL_PREFIX=${YARP_INSTALL_PREFIX}"
export YARP_CMAKE_OPTIONS="${YARP_CMAKE_OPTIONS} -DENABLE_yarpcar_h264:BOOL=ON"

# Print cmake build flags
echo "--------------------     BEGIN CMAKE FLAGS    --------------------"
echo " \
cmake -H\"${YARP_SOURCE_DIR}\" \
      -B\"${YARP_BINARY_DIR}\" \
      -G\"${YARP_CMAKE_GENERATOR}\" \
      -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
      ${YARP_CMAKE_OPTIONS} \
      ${YARP_EXTRA_CMAKE_OPTIONS}
" | sed 's/ -/ \\\n  -/g'
echo "--------------------      END CMAKE FLAGS     --------------------"

# Run CMake
cmake -H"${YARP_SOURCE_DIR}" \
      -B"${YARP_BINARY_DIR}" \
      -G"${YARP_CMAKE_GENERATOR}" \
      -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
      ${YARP_CMAKE_OPTIONS} \
      ${YARP_EXTRA_CMAKE_OPTIONS}
