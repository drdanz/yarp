// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <yarp/os/impl/String.h>
#include <yarp/os/Network.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/FrameGrabberInterfaces.h>

#include "TestList.h"

using namespace yarp::os;
using namespace yarp::os::impl;
using namespace yarp::sig;
using namespace yarp::dev;

class PolyDriverTest : public UnitTest {
public:
    virtual String getName() { return "PolyDriverTest"; }

    void testBasic() {
        report(0,"a very basic driver instantiation test");
        PolyDriver dd;
        Property p;
        p.put("device","test_grabber");
        bool result;
        result = dd.open(p);
        checkTrue(result,"open reported successful");
        IFrameGrabberImage *grabber = NULL;
        result = dd.view(grabber);
        checkTrue(result,"interface reported");
        ImageOf<PixelRgb> img;
        grabber->getImage(img);
        checkTrue(img.width()>0,"interface seems functional");
        result = dd.close();
        checkTrue(result,"close reported successful");
    }

    void testMonitor() {
        report(0,"test monitoring");
        Property p;
        p.put("device","grabber");
        p.put("subdevice","test_grabber");
        p.put("verbose",1);
        p.put("wrapped",1);
        PolyDriver dd(p);
        Bottle opts = dd.getOptions();
        checkTrue(opts.size()>0,"some options reported");
        //printf("Opts: %s\n", opts.toString().c_str());
        dd.close();
    }

    void testPropertyBug() {
        // guard against a bug reported by Martin Peniak
        report(0,"test Property bug reported by Martin Peniak");
        Property p;
        p.put("device","grabber");
        p.put("subdevice","test_grabber");
        p.put("verbose",1);
        p.put("wrapped",1);
        for (int i=0; i<5; i++) {
            PolyDriver *dd = new PolyDriver(p);
            delete dd;
            // bug may cause crash due to Monitor reporting to deallocated
            // driver
        }
    }

    virtual void runTests() {
        Network::setLocalMode(true);
        testBasic();
        testMonitor();
        testPropertyBug();
        Network::setLocalMode(false);
    }
};

static PolyDriverTest thePolyDriverTest;

UnitTest& getPolyDriverTest() {
    return thePolyDriverTest;
}

