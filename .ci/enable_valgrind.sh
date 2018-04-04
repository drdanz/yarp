#!/bin/bash

cmake ${YARP_BINARY_DIR} -DYARP_VALGRIND_TESTS=ON \
                         -DYARP_VALGRIND_DRD_TESTS=OFF \
                         -DYARP_VALGRIND_HELGRIND_TESTS=OFF \
                         -DYARP_VALGRIND_MEMCHECK_TESTS=ON \
                         -DYARP_VALGRIND_SGCHECK_TESTS=OFF \
                         -DYARP_DISABLE_FAILING_TESTS=ON # For now, disable tests with race conditions
