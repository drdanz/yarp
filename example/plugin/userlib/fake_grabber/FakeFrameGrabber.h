/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
class FakeFrameGrabber : public yarp::dev::IFrameGrabberImage, 
			 public yarp::dev::DeviceDriver {
private:
    int w, h;
public:
    FakeFrameGrabber() {
	h = w = 0;
    }

    bool open(int w, int h) {
	this->w = w;
	this->h = h;
	return w>0 && h>0;
    }

    virtual bool open(yarp::os::Searchable& config) { 
	// extract width and height configuration, if present
	// otherwise use 128x128
	int desiredWidth = config.check("w",yarp::os::Value(128)).asInt();
	int desiredHeight = config.check("h",yarp::os::Value(128)).asInt();
	return open(desiredWidth,desiredHeight);
    }

    virtual bool close() { 
	return true; // easy
    }

    virtual bool getImage(yarp::sig::ImageOf<yarp::sig::PixelRgb>& image);

    virtual int height() const {
	return h;
    }

    virtual int width() const {
	return w;
    }
};
