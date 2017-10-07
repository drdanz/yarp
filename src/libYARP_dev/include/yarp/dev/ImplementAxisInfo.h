/*
 * Copyright (C) 2015 iCub Facility, Istituto Italiano di Tecnologia
 * Authors: Marco Randazzo <marco.randazzo@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_DEV_IMPLEMENTAXISINFO_H
#define YARP_DEV_IMPLEMENTAXISINFO_H

#include <yarp/dev/ControlBoardInterfaces.h>

namespace yarp {
    namespace dev {
        class ImplementAxisInfo;
    }
}

class YARP_dev_API yarp::dev::ImplementAxisInfo: public IAxisInfo
{
protected:
    IAxisInfoRaw *iinfo;
    void *helper;
    double *temp1;
    double *temp2;


    /**
     * Initialize the internal data and alloc memory.
     * @param size is the number of controlled axes the driver deals with.
     * @param amap is a lookup table mapping axes onto physical drivers.
     * @return true if initialized succeeded, false if it wasn't executed, or assert.
     */
    bool initialize (int size, const int *amap);

    /**
     * Clean up internal data and memory.
     * @return true if uninitialization is executed, false otherwise.
     */
    bool uninitialize ();

public:
    /* Constructor.
     * @param y is the pointer to the class instance inheriting from this
     *  implementation.
     */
    ImplementAxisInfo(yarp::dev::IAxisInfoRaw *y);

    virtual ~ImplementAxisInfo();

    virtual bool getAxisName(int axis, yarp::os::ConstString& name) YARP_OVERRIDE;
    virtual bool getJointType(int axis, yarp::dev::JointTypeEnum& type) YARP_OVERRIDE;
};

#endif // YARP_DEV_IMPLEMENTAXISINFO_H
