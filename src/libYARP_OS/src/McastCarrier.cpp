// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright (C) 2006 RobotCub Consortium
 * Authors: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 *
 */

#include <yarp/conf/system.h>
#ifdef YARP_HAS_ACE

#include <stdlib.h>
#include <yarp/os/impl/McastCarrier.h>
#include <yarp/os/impl/Logger.h>
#include <yarp/os/Network.h>

using namespace yarp::os::impl;
using namespace yarp::os;

ElectionOf<McastCarrier,PeerRecord> *McastCarrier::caster = NULL;

ElectionOf<McastCarrier,PeerRecord>& McastCarrier::getCaster() {
    NetworkBase::lock();
    if (caster==NULL) {
        caster = new ElectionOf<McastCarrier,PeerRecord>;
        NetworkBase::unlock();
        if (caster==NULL) {
            YARP_ERROR(Logger::get(), "No memory for McastCarrier::caster");
            exit(1);
        }
    } else {
        NetworkBase::unlock();
    }
    return *caster;
}


#else

int McastCarrierDummySymbol = 42;

#endif




