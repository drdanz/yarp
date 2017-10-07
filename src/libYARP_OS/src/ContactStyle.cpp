/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <yarp/os/ContactStyle.h>


yarp::os::ContactStyle::ContactStyle() :
        admin(false),
        quiet(false),
        verboseOnSuccess(true),
        timeout(-1),
        carrier(""),
        expectReply(true),
        persistent(false), 
        persistenceType(yarp::os::ContactStyle::OPENENDED) {
}
