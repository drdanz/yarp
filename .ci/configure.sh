#!/bin/sh

# Prepare cmake options
export YARP_CMAKE_GENERATOR="Unix Makefiles"
export YARP_CMAKE_BUILD_TYPE="Release"

. scripts/admin/generate-cmake-options.sh $(hostname) $(lsb_release -cs) continuous

export YARP_INSTALL_PREFIX="${PWD}/install"
export YARP_CMAKE_OPTIONS="${CMAKE_OPTIONS} -DCMAKE_INSTALL_PREFIX=${YARP_INSTALL_PREFIX}"
export YARP_CMAKE_OPTIONS="${YARP_CMAKE_OPTIONS} -DENABLE_yarpcar_h264:BOOL=ON"
export YARP_CMAKE_OPTIONS="${YARP_CMAKE_OPTIONS} -DYARP_COMPILE_BINDINGS=ON -DCREATE_LUA=ON -DCREATE_TCL=ON -DCREATE_JAVA=ON -DCREATE_CSHARP=ON"

# Print cmake build flags
echo "--------------------     BEGIN CMAKE FLAGS    --------------------"
echo cmake -G"${YARP_CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} ${YARP_CMAKE_OPTIONS}
echo "--------------------      END CMAKE FLAGS     --------------------"

(cd build; cmake -G"${YARP_CMAKE_GENERATOR}" -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} ${YARP_CMAKE_OPTIONS} ..)

# Print cmake cache
echo "--------------------     BEGIN CMAKE CACHE    --------------------"
(cd build; cat CMakeCache.txt)
echo "--------------------      END CMAKE CACHE     --------------------"
