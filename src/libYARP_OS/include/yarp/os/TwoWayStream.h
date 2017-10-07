/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_TWOWAYSTREAM_H
#define YARP_OS_TWOWAYSTREAM_H

#include <yarp/conf/numeric.h>
#include <yarp/os/Contact.h>
#include <yarp/os/InputStream.h>
#include <yarp/os/OutputStream.h>

namespace yarp {
    namespace os {
        class TwoWayStream;
        class NullStream;
    }
}

/**
 * A stream which can be asked to perform bidirectional communication.
 * It need not actually be capable of communication in both directions,
 * in which case it should fail if requested to communicate in an
 * unsupported direction.
 */
class YARP_OS_API yarp::os::TwoWayStream {
public:
    /**
     * Destructor.
     */
    virtual ~TwoWayStream();

    /**
     * Get an InputStream to read from.
     *
     * @return the InputStream associated with this object.
     */
    virtual InputStream& getInputStream() = 0;

    /**
     * Get an OutputStream to write to.
     *
     * @return the InputStream associated with this object.
     */
    virtual OutputStream& getOutputStream() = 0;

    /**
     * Get the address of the local side of the stream.
     *
     * @return the address of the local side of the stream.
     * The address will be tagged as invalid if the stream is not set up.
     */
    virtual const Contact& getLocalAddress() = 0;

    /**
     * Get the address of the remote side of the stream.
     *
     * @return the address of the remote side of the stream.
     * The address will be tagged as invalid if the stream is not set up.
     */
    virtual const Contact& getRemoteAddress() = 0;

    /**
     *
     * Check if the stream is ok or in an error state.
     *
     * @return true iff the stream is ok
     *
     */
    virtual bool isOk() = 0;

    /**
     * Reset the stream.
     */
    virtual void reset() = 0;

    /**
     *
     * Terminate the stream.
     *
     */
    virtual void close() = 0;

    /**
     *
     * Mark the beginning of a logical packet.  This is a unit that
     * should be treated in an atomic fashion by YARP.  If any part
     * is corrupted, the whole should be dropped.
     *
     */
    virtual void beginPacket() = 0;

    /**
     *
     * Mark the end of a logical packet (see beginPacket).
     *
     */
    virtual void endPacket() = 0;
};


/**
 * A "null" stream, always invalid.
 */
class YARP_OS_API yarp::os::NullStream : public TwoWayStream,
                                         public InputStream,
                                         public OutputStream {
private:
    Contact address;
public:
    virtual ~NullStream();

    virtual InputStream& getInputStream() YARP_OVERRIDE;
    virtual OutputStream& getOutputStream() YARP_OVERRIDE;

    virtual const Contact& getLocalAddress() YARP_OVERRIDE;
    virtual const Contact& getRemoteAddress() YARP_OVERRIDE;

    virtual bool isOk() YARP_OVERRIDE;
    virtual void reset() YARP_OVERRIDE;
    virtual void close() YARP_OVERRIDE;
    virtual void beginPacket() YARP_OVERRIDE;
    virtual void endPacket() YARP_OVERRIDE;

    using yarp::os::InputStream::read;
    virtual YARP_SSIZE_T read(const Bytes& b) YARP_OVERRIDE;

    using yarp::os::OutputStream::write;
    virtual void write(const Bytes& b) YARP_OVERRIDE;
};

#endif // YARP_OS_TWOWAYSTREAM_H
