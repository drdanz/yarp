#!/bin/bash

# Build
(cd build; cmake --build . --config Release)

# Test
(cd build; ctest --output-on-failure --build . -C Release)

# Install
(cd build; cmake --build . --config Release --target install)
