/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "std_msgs/Empty" msg definition:
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_std_msgs_Empty_h
#define YARP_ROSMSG_std_msgs_Empty_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp
{
  namespace rosmsg
  {
    namespace std_msgs
    {
      class Empty : public yarp::os::idl::WirePortable
      {
        public:
        Empty()
        {
        }

        void clear()
        {
        }

        bool readBare( yarp::os::ConnectionReader& connection ) override
        {
          return !connection.isError();
        }

        bool readBottle( yarp::os::ConnectionReader& connection ) override
        {
          connection.convertTextMode();
          yarp::os::idl::WireReader reader( connection );
          if( !reader.readListHeader( 0 ))
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
          return !connection.isError();
        }

        bool writeBottle( yarp::os::ConnectionWriter& connection ) const override
        {
          connection.appendInt32( BOTTLE_TAG_LIST );
          connection.appendInt32( 0 );
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
        typedef yarp::os::idl::BareStyle< yarp::rosmsg::std_msgs::Empty >   rosStyle;
        typedef yarp::os::idl::BottleStyle< yarp::rosmsg::std_msgs::Empty > bottleStyle;

        // The name for this message, ROS will need this
        static constexpr const char* typeName = "std_msgs/Empty";

        // The checksum for this message, ROS will need this
        static constexpr const char* typeChecksum = "d41d8cd98f00b204e9800998ecf8427e";

        // The source text for this message, ROS will need this
        static constexpr const char* typeText = "\
\n\
";

        yarp::os::Type getType() const override
        {
          yarp::os::Type typ = yarp::os::Type::byName( typeName, typeName );
          typ.addProperty( "md5sum", yarp::os::Value( typeChecksum ));
          typ.addProperty( "message_definition", yarp::os::Value( typeText ));
          return typ;
        }
      };

    } // namespace std_msgs
  } // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_std_msgs_Empty_h
