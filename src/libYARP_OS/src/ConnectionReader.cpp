/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#include <yarp/os/ConnectionReader.h>
#include <yarp/os/impl/StreamConnectionReader.h>

using namespace yarp::os;
using namespace yarp::os::impl;

ConnectionReader::~ConnectionReader()
{
}

Bytes ConnectionReader::readEnvelope()
{
    return Bytes(YARP_NULLPTR, 0);
}

void ConnectionReader::setParentConnectionReader(ConnectionReader* parentConnectionReader)
{
    YARP_UNUSED(parentConnectionReader);
}

ConnectionReader *ConnectionReader::createConnectionReader(InputStream& is)
{
    StreamConnectionReader *reader = new StreamConnectionReader();
    Route r;
    reader->reset(is, YARP_NULLPTR, r, 0, false);
    return reader;
}

bool ConnectionReader::readFromStream(PortReader& portable, InputStream& is)
{
    StreamConnectionReader reader;
    Route r;
    reader.reset(is, YARP_NULLPTR, r, 0, false);
    return portable.read(reader);
}
