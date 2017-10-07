// This is an automatically generated file.
// Generated from this visualization_msgs_MarkerArray.msg definition:
//   visualization_msgs/Marker[] markers// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARPMSG_TYPE_visualization_msgs_MarkerArray
#define YARPMSG_TYPE_visualization_msgs_MarkerArray

#include <string>
#include <vector>
#include <yarp/os/Wire.h>
#include <yarp/os/idl/WireTypes.h>
#include "TickTime.h"
#include "std_msgs_Header.h"
#include "geometry_msgs_Point.h"
#include "geometry_msgs_Quaternion.h"
#include "geometry_msgs_Pose.h"
#include "geometry_msgs_Vector3.h"
#include "std_msgs_ColorRGBA.h"
#include "TickDuration.h"
#include "visualization_msgs_Marker.h"

class visualization_msgs_MarkerArray : public yarp::os::idl::WirePortable {
public:
  std::vector<visualization_msgs_Marker> markers;

  visualization_msgs_MarkerArray() {
  }

  void clear() {
    // *** markers ***
    markers.clear();
  }

  bool readBare(yarp::os::ConnectionReader& connection) YARP_OVERRIDE {
    // *** markers ***
    int len = connection.expectInt();
    markers.resize(len);
    for (int i=0; i<len; i++) {
      if (!markers[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  bool readBottle(yarp::os::ConnectionReader& connection) YARP_OVERRIDE {
    connection.convertTextMode();
    yarp::os::idl::WireReader reader(connection);
    if (!reader.readListHeader(1)) return false;

    // *** markers ***
    if (connection.expectInt()!=BOTTLE_TAG_LIST) return false;
    int len = connection.expectInt();
    markers.resize(len);
    for (int i=0; i<len; i++) {
      if (!markers[i].read(connection)) return false;
    }
    return !connection.isError();
  }

  using yarp::os::idl::WirePortable::read;
  bool read(yarp::os::ConnectionReader& connection) YARP_OVERRIDE {
    if (connection.isBareMode()) return readBare(connection);
    return readBottle(connection);
  }

  bool writeBare(yarp::os::ConnectionWriter& connection) YARP_OVERRIDE {
    // *** markers ***
    connection.appendInt(markers.size());
    for (size_t i=0; i<markers.size(); i++) {
      if (!markers[i].write(connection)) return false;
    }
    return !connection.isError();
  }

  bool writeBottle(yarp::os::ConnectionWriter& connection) YARP_OVERRIDE {
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(1);

    // *** markers ***
    connection.appendInt(BOTTLE_TAG_LIST);
    connection.appendInt(markers.size());
    for (size_t i=0; i<markers.size(); i++) {
      if (!markers[i].write(connection)) return false;
    }
    connection.convertTextMode();
    return !connection.isError();
  }

  using yarp::os::idl::WirePortable::write;
  bool write(yarp::os::ConnectionWriter& connection) YARP_OVERRIDE {
    if (connection.isBareMode()) return writeBare(connection);
    return writeBottle(connection);
  }

  // This class will serialize ROS style or YARP style depending on protocol.
  // If you need to force a serialization style, use one of these classes:
  typedef yarp::os::idl::BareStyle<visualization_msgs_MarkerArray> rosStyle;
  typedef yarp::os::idl::BottleStyle<visualization_msgs_MarkerArray> bottleStyle;

  // Give source text for class, ROS will need this
  yarp::os::ConstString getTypeText() {
    return "visualization_msgs/Marker[] markers\n================================================================================\n\
MSG: visualization_msgs/Marker\n\
# See http://www.ros.org/wiki/rviz/DisplayTypes/Marker and http://www.ros.org/wiki/rviz/Tutorials/Markers%3A%20Basic%20Shapes for more information on using this message with rviz\n\
\n\
uint8 ARROW=0\n\
uint8 CUBE=1\n\
uint8 SPHERE=2\n\
uint8 CYLINDER=3\n\
uint8 LINE_STRIP=4\n\
uint8 LINE_LIST=5\n\
uint8 CUBE_LIST=6\n\
uint8 SPHERE_LIST=7\n\
uint8 POINTS=8\n\
uint8 TEXT_VIEW_FACING=9\n\
uint8 MESH_RESOURCE=10\n\
uint8 TRIANGLE_LIST=11\n\
\n\
uint8 ADD=0\n\
uint8 MODIFY=0\n\
uint8 DELETE=2\n\
uint8 DELETEALL=3\n\
\n\
Header header                        # header for time/frame information\n\
string ns                            # Namespace to place this object in... used in conjunction with id to create a unique name for the object\n\
int32 id                           # object ID useful in conjunction with the namespace for manipulating and deleting the object later\n\
int32 type                         # Type of object\n\
int32 action                         # 0 add/modify an object, 1 (deprecated), 2 deletes an object, 3 deletes all objects\n\
geometry_msgs/Pose pose                 # Pose of the object\n\
geometry_msgs/Vector3 scale             # Scale of the object 1,1,1 means default (usually 1 meter square)\n\
std_msgs/ColorRGBA color             # Color [0.0-1.0]\n\
duration lifetime                    # How long the object should last before being automatically deleted.  0 means forever\n\
bool frame_locked                    # If this marker should be frame-locked, i.e. retransformed into its frame every timestep\n\
\n\
#Only used if the type specified has some use for them (eg. POINTS, LINE_STRIP, ...)\n\
geometry_msgs/Point[] points\n\
#Only used if the type specified has some use for them (eg. POINTS, LINE_STRIP, ...)\n\
#number of colors must either be 0 or equal to the number of points\n\
#NOTE: alpha is not yet used\n\
std_msgs/ColorRGBA[] colors\n\
\n\
# NOTE: only used for text markers\n\
string text\n\
\n\
# NOTE: only used for MESH_RESOURCE markers\n\
string mesh_resource\n\
bool mesh_use_embedded_materials\n================================================================================\n\
MSG: std_msgs/Header\n\
[std_msgs/Header]:\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data\n\
# in a particular coordinate frame.\n\
#\n\
# sequence ID: consecutively increasing ID\n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of postion and orientation. \n\
geometry_msgs/Point position\n\
geometry_msgs/Quaternion orientation\n================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n================================================================================\n\
MSG: geometry_msgs/Vector3\n\
# This represents a vector in free space.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n================================================================================\n\
MSG: std_msgs/ColorRGBA\n\
float32 r\n\
float32 g\n\
float32 b\n\
float32 a";
  }

  // Name the class, ROS will need this
  yarp::os::Type getType() YARP_OVERRIDE {
    yarp::os::Type typ = yarp::os::Type::byName("visualization_msgs/MarkerArray","visualization_msgs/MarkerArray");
    typ.addProperty("md5sum",yarp::os::Value("d155b9ce5188fbaf89745847fd5882d7"));
    typ.addProperty("message_definition",yarp::os::Value(getTypeText()));
    return typ;
  }
};

#endif
