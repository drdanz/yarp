/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */


#ifndef YARP_DEV_DEVICEGROUP_H
#define YARP_DEV_DEVICEGROUP_H

#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/ServiceInterfaces.h>


namespace yarp{
    namespace dev {
        class DeviceGroup;
    }
}

/**
 * @ingroup dev_impl_wrapper
 *
 * Lets you make a bunch of devices as a group.
 *
 */
class YARP_dev_API yarp::dev::DeviceGroup : public DeviceDriver,
                                            public IService {

public:
    DeviceGroup() {
        implementation = NULL;
    }

    virtual ~DeviceGroup();

    virtual bool open(yarp::os::Searchable& config) YARP_OVERRIDE;

    virtual bool close() YARP_OVERRIDE {
        return closeMain();
    }

    virtual bool startService() YARP_OVERRIDE;

    virtual bool stopService() YARP_OVERRIDE {
        return close();
    }

    virtual bool updateService() YARP_OVERRIDE;

private:
    void *implementation;

    bool closeMain();

    PolyDriver source, sink;

    bool open(const char *key, PolyDriver& poly,
              yarp::os::Searchable& config, const char *comment);
};


#endif // YARP_DEV_DEVICEGROUP_H
