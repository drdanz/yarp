/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Author: Lorenzo Natale
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <yarp/os/Bottle.h>
#include <yarp/os/Port.h>
#include <yarp/os/Thread.h>

#include <string>
#include <list>


class CollatzServer : public yarp::os::Thread
{
protected:
    yarp::os::Port port;
    std::string portName;
    std::list<unsigned int> table;
    unsigned int curNum;

    void tickItem(const unsigned int num);
    void generateItem(unsigned int &num, unsigned int &thres);

public:
    CollatzServer(const std::string &_portName);

    virtual bool threadInit();
    virtual void run();
    virtual void threadRelease();
};


#endif

