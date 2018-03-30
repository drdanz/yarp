#!/bin/bash

# Test
(cd build; ctest --output-on-failure --build . -C Release)
