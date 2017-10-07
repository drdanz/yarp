/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <yarp/os/Bytes.h>


yarp::os::Bytes::Bytes() :
        data(YARP_NULLPTR),
        len(0)
{
}

yarp::os::Bytes::Bytes(char *data, size_t len) :
        data(data),
        len(len)
{
}

size_t yarp::os::Bytes::length() const
{
    return len;
}

char *yarp::os::Bytes::get() const
{
    return data;
}
