/*
 * Copyright (C) 2009 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_OS_RPCCLIENT_H
#define YARP_OS_RPCCLIENT_H

#include <yarp/os/AbstractContactable.h>

namespace yarp {
    namespace os {
        class RpcClient;
    }
}

/**
 * \ingroup comm_class
 *
 * A port that is specialized as an RPC client.  That is, it expects to
 * connect to a single server, and receive replies on the same connection.
 *
 */
class YARP_OS_API yarp::os::RpcClient : public AbstractContactable {
public:
    using AbstractContactable::open;


    /**
     * Constructor.
     */
    RpcClient();

    /**
     * Destructor.
     */
    virtual ~RpcClient();

    // documented in UnbufferedContactable
    virtual bool read(PortReader& reader, bool willReply = false) YARP_OVERRIDE;

    // documented in UnbufferedContactable
    virtual bool reply(PortWriter& writer) YARP_OVERRIDE;

    // documented in UnbufferedContactable
    virtual bool replyAndDrop(PortWriter& writer) YARP_OVERRIDE;


    void setInputMode(bool expectInput) YARP_OVERRIDE;
    void setOutputMode(bool expectOutput) YARP_OVERRIDE;
    void setRpcMode(bool expectRpc) YARP_OVERRIDE;

    virtual Port& asPort() YARP_OVERRIDE {
        return port;
    }

    virtual const Port& asPort() const YARP_OVERRIDE {
        return port;
    }

private:
    // an RpcClient may be implemented with a regular port
    Port port;

    // forbid copy constructor and assignment operator by making them private
    // and not implementing them
    RpcClient(const RpcClient& alt);
    const RpcClient& operator = (const RpcClient& alt);
};

#endif // YARP_OS_RPCCLIENT_H
