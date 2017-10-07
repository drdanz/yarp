/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_STRINGINPUTSTREAM_H
#define YARP_OS_STRINGINPUTSTREAM_H

#include <yarp/os/InputStream.h>
#include <yarp/os/ConstString.h>

namespace yarp {
    namespace os {
        class StringInputStream;
    }
}

/**
 * An InputStream that reads from a string.  Handy For testing purposes.
 */
class yarp::os::StringInputStream : public InputStream {
public:
    using InputStream::read;

    StringInputStream() {
        at = 0;
        data = "";
    }

    void reset() {
        at = 0;
        data = "";
    }

    void reset(const ConstString& str) {
        at = 0;
        data = str;
    }

    void add(const ConstString& txt) {
        data += txt;
    }

    void add(const Bytes& b) {
        for (size_t i=0; i<b.length(); i++) {
            data += b.get()[i];
        }
    }

    virtual YARP_SSIZE_T read(const Bytes& b) YARP_OVERRIDE {
        char *base = b.get();
        size_t space = b.length();
        YARP_SSIZE_T ct = 0;
        for (size_t i=0; i<space; i++) {
            if (at<data.length()) {
                base[i] = data[at];
                at++;
                ct++;
            }
        }
        return ct;
    }

    virtual void close() YARP_OVERRIDE {
    }

    virtual ConstString toString() {
        return data;
    }

    virtual bool isOk() YARP_OVERRIDE {
        return true;
    }

private:
    ConstString data;
    unsigned int at;
};

#endif // YARP_OS_STRINGINPUTSTREAM_H
