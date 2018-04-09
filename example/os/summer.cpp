/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/Bottle.h>
#include <iostream>

using yarp::os::Network;
using yarp::os::BufferedPort;
using yarp::os::Bottle;

int main(int argc, char* argv[])
{
    Network yarp;
    BufferedPort<Bottle> port;
    port.open("/summer");
    while (true) {
        std::cout << "waiting for input" << std::endl;
        Bottle* input = port.read();
        if (input != NULL) {
            std::cout << "got " << input->toString().c_str() << std::endl;
            double total = 0;
            for (int i = 0; i < input->size(); i++) {
                total += input->get(i).asDouble();
            }
            Bottle& output = port.prepare();
            output.clear();
            output.addString("total");
            output.addDouble(total);
            std::cout << "writing " << output.toString().c_str() << std::endl;
            port.write();
        }
    }
    return 0;
}
