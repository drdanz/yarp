// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

/*
 * Copyright: (C) 2010 RobotCub Consortium
 * Author: Paul Fitzpatrick
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#include <stdio.h>
#include <yarp/os/all.h>
using namespace yarp::os;

class DataProcessor : public TypedReaderCallback<Bottle>, public PortReader {
     virtual void onRead(Bottle& b) {
          // process data in b
         printf("Got one-way message: %s\n", b.toString().c_str());
     }

    virtual bool read(ConnectionReader& connection) {
        Bottle in, out;
        in.read(connection);
        // process data "in", prepare "out"
        printf("Got message to reply to: %s\n", in.toString().c_str());  
        out.clear();
        out.add("acknowledge");
        out.append(in);
        ConnectionWriter *returnToSender = connection.getWriter();
        if (returnToSender!=NULL) {
            out.write(*returnToSender);
        }
        return true;
    }
};
DataProcessor processor;



int main() {
    Network yarp;
    
    DataProcessor processor;
    BufferedPort<Bottle> p;
    p.useCallback(processor);  // input should go to processor.onRead()
    p.setReplier(processor);   // input with replt goes to processor.read()
    p.open("/in");          // Give it a name on the network.
    while (true) {
        printf("main thread free to do whatever it wants\n");
        Time::delay(10);
    }
    
    return 0;
}
