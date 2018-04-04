#!/bin/bash

if (( $# != 1 )); then
    echo "Usage: $0 [language]"
    exit 1
fi
language=$(echo "$1" | tr '[:lower:]' '[:upper:]')


export YARP_BINDINGS_CMAKE_OPTIONS="-DYARP_COMPILE_BINDINGS=ON -DCREATE_${language}=ON"
if [ "${language}" = "PYTHON" -o "${language}" = "PYTHON2" ]; then
    export YARP_BINDINGS_CMAKE_OPTIONS="${YARP_BINDINGS_CMAKE_OPTIONS} -DYARP_USE_PYTHON_VERSION=2"
elif [ "${language}" = "PYTHON3" ]; then
    export YARP_BINDINGS_CMAKE_OPTIONS="${YARP_BINDINGS_CMAKE_OPTIONS} -DYARP_USE_PYTHON_VERSION=3"
fi


################################################################################
echo "Building ${language} bindings - Out of source build (build tree)"
export BINDINGS_SOURCE_DIR="${CI_PROJECT_DIR}/bindings"
export BINDINGS_BINARY_DIR="${BINDINGS_SOURCE_DIR}/build-${language}"
export YARP_DIR="${YARP_BINARY_DIR}"

cmake -H"${BINDINGS_SOURCE_DIR}" \
      -B"${BINDINGS_BINARY_DIR}" \
      -G"${YARP_CMAKE_GENERATOR}" \
      -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
      -DYARP_DIR=${YARP_DIR} \
      ${YARP_BINDINGS_CMAKE_OPTIONS}

cmake --build ${BINDINGS_BINARY_DIR} --config ${YARP_CMAKE_BUILD_TYPE}


################################################################################
echo "Building ${language} bindings - Out of source build (install tree)"
export BINDINGS_SOURCE_DIR="${YARP_INSTALL_PREFIX}/share/yarp/bindings"
export BINDINGS_BINARY_DIR="${BINDINGS_SOURCE_DIR}/build-${language}"
export YARP_DIR=${YARP_INSTALL_DIR}

cmake -H"${BINDINGS_SOURCE_DIR}" \
      -B"${BINDINGS_BINARY_DIR}" \
      -G"${YARP_CMAKE_GENERATOR}" \
      -DCMAKE_BUILD_TYPE=${YARP_CMAKE_BUILD_TYPE} \
      -DYARP_DIR=${YARP_DIR} \
      ${YARP_BINDINGS_CMAKE_OPTIONS}

cmake --build ${BINDINGS_BINARY_DIR} --config ${YARP_CMAKE_BUILD_TYPE}


################################################################################
echo "Building ${language} bindings - Nested build"
unset BINDINGS_SOURCE_DIR
unset BINDINGS_BINARY_DIR
unset YARP_DIR

cmake ${YARP_BINARY_DIR} ${YARP_BINDINGS_CMAKE_OPTIONS}
cmake --build ${YARP_BINARY_DIR} --config ${YARP_CMAKE_BUILD_TYPE}
