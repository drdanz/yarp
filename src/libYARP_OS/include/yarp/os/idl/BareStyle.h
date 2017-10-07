/*
 * Copyright (C) 2014 iCub Facility
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_IDL_BARESTYLE_H
#define YARP_OS_IDL_BARESTYLE_H

#include <yarp/os/idl/WirePortable.h>
#include <yarp/os/idl/WireReader.h>
#include <yarp/os/idl/WireWriter.h>

namespace yarp {
    namespace os {
        namespace idl {
            template <class T> class BareStyle;
        }
    }
}

template <class T>
class yarp::os::idl::BareStyle : public T {
public:
    virtual bool read(yarp::os::ConnectionReader& reader) {
        return T::readBare(reader);
    }

    virtual bool write(yarp::os::ConnectionWriter& writer) {
        return T::writeBare(writer);
    }
};

#endif // YARP_OS_IDL_BARESTYLE_H
