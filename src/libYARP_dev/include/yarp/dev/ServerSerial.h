/*
 * Copyright (C) 2006 Alex Bernardino & Carlos Beltran-Gonzalez
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef YARP_DEV_SERVERSERIAL_H
#define YARP_DEV_SERVERSERIAL_H

#include <cstdio>
#include <cstdlib>

#include <yarp/os/BufferedPort.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/SerialInterfaces.h>
#include <yarp/os/Time.h>
#include <yarp/os/Network.h>
#include <yarp/os/Thread.h>
#include <yarp/os/Vocab.h>
#include <yarp/os/Bottle.h>


using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::dev;


namespace yarp
{
    namespace dev
    {
        class ServerSerial;
        class ImplementCallbackHelper2;
    }
}

/**
 * Callback implementation after buffered input.
 */
class yarp::dev::ImplementCallbackHelper2 : public TypedReaderCallback<Bottle> {
protected:
    ISerialDevice *ser;

public:
    /**
     * Constructor.
     * @param x is the instance of the container class using the callback.
     */
    ImplementCallbackHelper2();
    ImplementCallbackHelper2(yarp::dev::ServerSerial *x);

    using yarp::os::TypedReaderCallback<Bottle>::onRead;
    /**
     * Callback function.
     * @param b is the Bottle being received.
     */
    virtual void onRead(Bottle& b) YARP_OVERRIDE;
};


/**
 * @ingroup dev_impl_wrapper
 *
 * Export a serial sensor.
 * The network interface is composed by two ports.
 * The input port accepts bottles and sends their contents as
 * text to the serial port.
 * The output port streams out whatever information it gets in the
 * serial port as text bottles.
 *
 * @author Alex Bernardino
 */
class YARP_dev_API yarp::dev::ServerSerial : public DeviceDriver,
                                             public ISerialDevice,
                                             private Thread
{
private:
    bool verb;
    PolyDriver poly;
    Port toDevice;
    Port fromDevice;

    PortWriterBuffer <Bottle> reply_buffer;
    PortReaderBuffer <Bottle> command_buffer;

    ISerialDevice *serial;
    yarp::dev::ImplementCallbackHelper2 callback_impl;


    bool closeMain() {
        if (Thread::isRunning()) {
            Thread::stop();
        }
        //close the port connection here
        toDevice.close();
        fromDevice.close();
        poly.close();
        return true;
    }

public:
    /**
     * Constructor.
     */
    ServerSerial();

    virtual ~ServerSerial();

    virtual bool send(const Bottle& msg) YARP_OVERRIDE;
    virtual bool send(char *msg, size_t size) YARP_OVERRIDE;
    virtual bool receive(Bottle& msg) YARP_OVERRIDE;
    virtual int receiveChar(char& c) YARP_OVERRIDE;
    virtual int flush () YARP_OVERRIDE;
    virtual int receiveLine(char* line, const int MaxLineLength) YARP_OVERRIDE;
    virtual int receiveBytes(unsigned char* bytes, const int size) YARP_OVERRIDE;
    virtual bool setDTR(bool enable) YARP_OVERRIDE;

    /**
    * Default open() method.
    * @return always false since initialization requires certain parameters.
    */
    virtual bool open();

    /**
    * Close the device driver by deallocating all resources and closing ports.
    * @return true if successful or false otherwise.
    */
    virtual bool close() YARP_OVERRIDE;

    /**
     * Open the device driver.
     *
     * @param prop is a Searchable object that contains the parameters to use.
     * Allowed parameters are:
     * - verbose or v to print diagnostic information while running,
     * - name to specify the prefix of the port names
     * and all parameters requied by the wrapped device driver.
     * @return true iff the object could be configured.
     */
    virtual bool open(Searchable& prop) YARP_OVERRIDE;

    /**
     * The thread main loop deals with writing on ports here.
     */
    virtual void run() YARP_OVERRIDE;
};

#endif // YARP_DEV_SERVERSERIAL_H
