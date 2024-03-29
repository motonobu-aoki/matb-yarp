/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "geometry_msgs/PoseStamped" msg definition:
//   # A Pose with reference coordinate frame and timestamp
//   Header header
//   Pose pose
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_geometry_msgs_PoseStamped_h
#define YARP_ROSMSG_geometry_msgs_PoseStamped_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/std_msgs/Header.h>
#include <yarp/rosmsg/geometry_msgs/Pose.h>

namespace yarp
{
  namespace rosmsg
  {
    namespace geometry_msgs
    {
      class PoseStamped : public yarp::os::idl::WirePortable
      {
        public:
        yarp::rosmsg::std_msgs::Header    header;
        yarp::rosmsg::geometry_msgs::Pose pose;

        PoseStamped() : header(), pose()
        {
        }

        void clear()
        {
          // *** header ***
          header.clear();

          // *** pose ***
          pose.clear();
        }

        bool readBare( yarp::os::ConnectionReader& connection ) override
        {
          // *** header ***
          if( !header.read( connection ))
          {
            return false;
          }

          // *** pose ***
          if( !pose.read( connection ))
          {
            return false;
          }
          return !connection.isError();
        }

        bool readBottle( yarp::os::ConnectionReader& connection ) override
        {
          connection.convertTextMode();
          yarp::os::idl::WireReader reader( connection );
          if( !reader.readListHeader( 2 ))
          {
            return false;
          }

          // *** header ***
          if( !header.read( connection ))
          {
            return false;
          }

          // *** pose ***
          if( !pose.read( connection ))
          {
            return false;
          }
          return !connection.isError();
        }
        using yarp::os::idl::WirePortable::read;
        bool read( yarp::os::ConnectionReader& connection ) override
        {
          return ( connection.isBareMode() ? readBare( connection ) : readBottle( connection ));
        }

        bool writeBare( yarp::os::ConnectionWriter& connection ) const override
        {
          // *** header ***
          if( !header.write( connection ))
          {
            return false;
          }

          // *** pose ***
          if( !pose.write( connection ))
          {
            return false;
          }
          return !connection.isError();
        }

        bool writeBottle( yarp::os::ConnectionWriter& connection ) const override
        {
          connection.appendInt32( BOTTLE_TAG_LIST );
          connection.appendInt32( 2 );

          // *** header ***
          if( !header.write( connection ))
          {
            return false;
          }

          // *** pose ***
          if( !pose.write( connection ))
          {
            return false;
          }
          connection.convertTextMode();
          return !connection.isError();
        }
        using yarp::os::idl::WirePortable::write;
        bool write( yarp::os::ConnectionWriter& connection ) const override
        {
          return ( connection.isBareMode() ? writeBare( connection ) : writeBottle( connection ));
        }

        // This class will serialize ROS style or YARP style depending on protocol.
        // If you need to force a serialization style, use one of these classes:
        typedef yarp::os::idl::BareStyle< yarp::rosmsg::geometry_msgs::PoseStamped >   rosStyle;
        typedef yarp::os::idl::BottleStyle< yarp::rosmsg::geometry_msgs::PoseStamped > bottleStyle;

        // The name for this message, ROS will need this
        static constexpr const char* typeName = "geometry_msgs/PoseStamped";

        // The checksum for this message, ROS will need this
        static constexpr const char* typeChecksum = "d3812c3cbc69362b77dc0b19b345f8f5";

        // The source text for this message, ROS will need this
        static constexpr const char* typeText = "\
# A Pose with reference coordinate frame and timestamp\n\
Header header\n\
Pose pose\n\
\n\
================================================================================\n\
MSG: std_msgs/Header\n\
# Standard metadata for higher-level stamped data types.\n\
# This is generally used to communicate timestamped data \n\
# in a particular coordinate frame.\n\
# \n\
# sequence ID: consecutively increasing ID \n\
uint32 seq\n\
#Two-integer timestamp that is expressed as:\n\
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n\
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n\
# time-handling sugar is provided by the client library\n\
time stamp\n\
#Frame this data is associated with\n\
# 0: no frame\n\
# 1: global frame\n\
string frame_id\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Pose\n\
# A representation of pose in free space, composed of position and orientation. \n\
Point position\n\
Quaternion orientation\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Point\n\
# This contains the position of a point in free space\n\
float64 x\n\
float64 y\n\
float64 z\n\
\n\
================================================================================\n\
MSG: geometry_msgs/Quaternion\n\
# This represents an orientation in free space in quaternion form.\n\
\n\
float64 x\n\
float64 y\n\
float64 z\n\
float64 w\n\
";

        yarp::os::Type getType() const override
        {
          yarp::os::Type typ = yarp::os::Type::byName( typeName, typeName );
          typ.addProperty( "md5sum", yarp::os::Value( typeChecksum ));
          typ.addProperty( "message_definition", yarp::os::Value( typeText ));
          return typ;
        }
      };

    } // namespace geometry_msgs
  } // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_geometry_msgs_PoseStamped_h
