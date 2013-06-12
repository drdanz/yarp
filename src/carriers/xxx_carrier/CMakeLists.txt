# Copyright (C) 2013  iCub Facility, Istituto Italiano di Tecnologia
# Author: Daniele E. Domenichelli <daniele.domenichelli@iit.it>
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

########################################################################
# From YarpPlugin.cmake
macro(YARP_ADD_CARRIER_FINGERPRINT _file_name)
    get_filename_component(out_name ${_file_name} NAME)
    configure_file(${_file_name} ${CMAKE_BINARY_DIR}/plugins/${out_name} COPYONLY)
    if(YARP_TREE_INCLUDE_DIRS)
        install(FILES ${CMAKE_BINARY_DIR}/plugins/${out_name}
                COMPONENT runtime
                DESTINATION share/yarp/plugins)
    endif(YARP_TREE_INCLUDE_DIRS)
endmacro(YARP_ADD_CARRIER_FINGERPRINT)
########################################################################


set(XXX_HDRS XXXCarrier.h XXXStream.h)
set(XXX_SRCS XXXCarrier.cpp XXXStream.cpp)

add_library(yarp_xxx MODULE ${XXX_SRCS})

install(TARGETS yarp_xxx
        COMPONENT runtime
        DESTINATION lib)


yarp_add_carrier_fingerprint(xxx.ini)

target_link_libraries(yarp_xxx YARP_OS YARP_sig)
target_link_libraries(yarp_xxx ${ACE_LIBRARIES})
