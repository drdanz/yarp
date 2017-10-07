/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Marco Randazzo <marco.randazzo@iit.it>
 * CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT
 */

#ifndef YARP_DEV_LOCATIONSSERVER_LOCATIONSSERVER_H
#define YARP_DEV_LOCATIONSSERVER_LOCATIONSSERVER_H

#include <map>
#include <yarp/os/Network.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/dev/PreciselyTimed.h>
#include <yarp/dev/ControlBoardInterfaces.h>
#include <yarp/dev/ControlBoardHelpers.h>
#include <yarp/sig/Vector.h>
#include <yarp/os/Semaphore.h>
#include <yarp/os/Time.h>
#include <yarp/os/ConstString.h>
#include <yarp/dev/PolyDriver.h>
#include <yarp/dev/INavigation2D.h>
#include <yarp/os/Publisher.h>
#include <yarp/os/Subscriber.h>
#include <yarp/os/Node.h>
#include "include/visualization_msgs_MarkerArray.h"

namespace yarp {
    namespace dev {
        class LocationsServer;
    }
}

#define DEFAULT_THREAD_PERIOD 20 //ms


/**
* @ingroup dev_impl_wrapper
*
*/

typedef yarp::os::Publisher<visualization_msgs_MarkerArray> MarkerArrayPublisher;

#define V3_X 0
#define V3_Y 1
#define V3_Z 2

class yarp::dev::LocationsServer : public DeviceDriver , public yarp::os::PortReader

{
#ifndef DOXYGEN_SHOULD_SKIP_THIS
protected:

    yarp::os::Mutex       m_mutex;
    yarp::os::Port        m_rpc_port;
    yarp::os::ConstString m_local_name;
    int                   m_period;
    yarp::os::Node*       m_rosNode;
    bool                  m_ros_enabled;
    MarkerArrayPublisher  m_rosPublisherPort;

#endif /*DOXYGEN_SHOULD_SKIP_THIS*/

private:
    std::map<std::string, yarp::dev::Map2DLocation> m_locations;

public:
    /* DeviceDriver methods */
    bool         open(yarp::os::Searchable& config) override;
    bool         close() override;
    virtual bool read(yarp::os::ConnectionReader& connection) override;
    bool         updateVizMarkers();
    bool         load_locations(yarp::os::ConstString locations_file);
    bool         save_locations(yarp::os::ConstString locations_file);
};

#endif // YARP_DEV_LOCATIONSSERVER_LOCATIONSSERVER_H
