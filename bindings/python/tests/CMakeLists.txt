# Copyright (C) 2006-2021 Istituto Italiano di Tecnologia (IIT)
# All rights reserved.
#
# This software may be modified and distributed under the terms of the
# BSD-3-Clause license. See the accompanying LICENSE file for details.

macro(add_python_unit_test pythonscript)
  if(PYTHON_EXECUTABLE)
    string(REGEX REPLACE "^test_" "bindings::python::" name "${pythonscript}")
    string(REGEX REPLACE "\\.py$" "" name "${name}")
    add_test(NAME "${name}" COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/${pythonscript})
    set_tests_properties("${name}" PROPERTIES ENVIRONMENT "PYTHONPATH=$<TARGET_FILE_DIR:${SWIG_MODULE_yarp_python_REAL_NAME}>")
    set_tests_properties("${name}" PROPERTIES TIMEOUT 60)
  endif()
endmacro()

add_python_unit_test(test_buffered_port.py)
add_python_unit_test(test_image.py)
add_python_unit_test(test_load.py)
add_python_unit_test(test_vector.py)
add_python_unit_test(test_thread.py)
