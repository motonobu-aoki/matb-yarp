/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "nav_msgs/GetPlan" msg definition:
//   # Get a plan from the current position to the goal Pose 
//   
//   # The start pose for the plan
//   geometry_msgs/PoseStamped start
//   
//   # The final pose of the goal position
//   geometry_msgs/PoseStamped goal
//   
//   # If the goal is obstructed, how many meters the planner can 
//   # relax the constraint in x and y before failing. 
//   float32 tolerance
//   ---
//   nav_msgs/Path plan
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_nav_msgs_GetPlan_h
#define YARP_ROSMSG_nav_msgs_GetPlan_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/geometry_msgs/PoseStamped.h>

namespace yarp
{
  namespace rosmsg
  {
    namespace nav_msgs
    {
      class GetPlan : public yarp::os::idl::WirePortable
      {
        public:
        yarp::rosmsg::geometry_msgs::PoseStamped start;
        yarp::rosmsg::geometry_msgs::PoseStamped goal;
        yarp::conf::float32_t                    tolerance;

        GetPlan() : start(), goal(), tolerance( 0.0f )
        {
        }

        void clear()
        {
          // *** start ***
          start.clear();

          // *** goal ***
          goal.clear();

          // *** tolerance ***
          tolerance = 0.0f;
        }

        bool readBare( yarp::os::ConnectionReader& connection ) override
        {
          // *** start ***
          if( !start.read( connection ))
          {
            return false;
          }

          // *** goal ***
          if( !goal.read( connection ))
          {
            return false;
          }

          // *** tolerance ***
          tolerance = connection.expectFloat32();
          return !connection.isError();
        }

        bool readBottle( yarp::os::ConnectionReader& connection ) override
        {
          connection.convertTextMode();
          yarp::os::idl::WireReader reader( connection );
          if( !reader.readListHeader( 3 ))
          {
            return false;
          }

          // *** start ***
          if( !start.read( connection ))
          {
            return false;
          }

          // *** goal ***
          if( !goal.read( connection ))
          {
            return false;
          }

          // *** tolerance ***
          tolerance = reader.expectFloat32();
          return !connection.isError();
        }
        using yarp::os::idl::WirePortable::read;
        bool read( yarp::os::ConnectionReader& connection ) override
        {
          return ( connection.isBareMode() ? readBare( connection ) : readBottle( connection ));
        }

        bool writeBare( yarp::os::ConnectionWriter& connection ) const override
        {
          // *** start ***
          if( !start.write( connection ))
          {
            return false;
          }

          // *** goal ***
          if( !goal.write( connection ))
          {
            return false;
          }

          // *** tolerance ***
          connection.appendFloat32( tolerance );
          return !connection.isError();
        }

        bool writeBottle( yarp::os::ConnectionWriter& connection ) const override
        {
          connection.appendInt32( BOTTLE_TAG_LIST );
          connection.appendInt32( 3 );

          // *** start ***
          if( !start.write( connection ))
          {
            return false;
          }

          // *** goal ***
          if( !goal.write( connection ))
          {
            return false;
          }

          // *** tolerance ***
          connection.appendInt32( BOTTLE_TAG_FLOAT32 );
          connection.appendFloat32( tolerance );
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
        typedef yarp::os::idl::BareStyle< yarp::rosmsg::nav_msgs::GetPlan >   rosStyle;
        typedef yarp::os::idl::BottleStyle< yarp::rosmsg::nav_msgs::GetPlan > bottleStyle;

        // The name for this message, ROS will need this
        static constexpr const char* typeName = "nav_msgs/GetPlan";

        // The checksum for this message, ROS will need this
        static constexpr const char* typeChecksum = "e25a43e0752bcca599a8c2eef8282df8";

        // The source text for this message, ROS will need this
        static constexpr const char* typeText = "\
# Get a plan from the current position to the goal Pose \n\
\n\
# The start pose for the plan\n\
geometry_msgs/PoseStamped start\n\
\n\
# The final pose of the goal position\n\
geometry_msgs/PoseStamped goal\n\
\n\
# If the goal is obstructed, how many meters the planner can \n\
# relax the constraint in x and y before failing. \n\
float32 tolerance\n\
---\n\
nav_msgs/Path plan\n\
\n\
================================================================================\n\
MSG: geometry_msgs/PoseStamped\n\
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

    } // namespace nav_msgs
  } // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_nav_msgs_GetPlan_h
