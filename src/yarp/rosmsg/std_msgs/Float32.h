/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "std_msgs/Float32" msg definition:
//   float32 data// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_std_msgs_Float32_h
#define YARP_ROSMSG_std_msgs_Float32_h

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
      class Float32 : public yarp::os::idl::WirePortable
      {
        public:
        yarp::conf::float32_t data;

        Float32() : data( 0.0f )
        {
        }

        void clear()
        {
          // *** data ***
          data = 0.0f;
        }

        bool readBare( yarp::os::ConnectionReader& connection ) override
        {
          // *** data ***
          data = connection.expectFloat32();
          return !connection.isError();
        }

        bool readBottle( yarp::os::ConnectionReader& connection ) override
        {
          connection.convertTextMode();
          yarp::os::idl::WireReader reader( connection );
          if( !reader.readListHeader( 1 ))
          {
            return false;
          }

          // *** data ***
          data = reader.expectFloat32();
          return !connection.isError();
        }
        using yarp::os::idl::WirePortable::read;
        bool read( yarp::os::ConnectionReader& connection ) override
        {
          return ( connection.isBareMode() ? readBare( connection ) : readBottle( connection ));
        }

        bool writeBare( yarp::os::ConnectionWriter& connection ) const override
        {
          // *** data ***
          connection.appendFloat32( data );
          return !connection.isError();
        }

        bool writeBottle( yarp::os::ConnectionWriter& connection ) const override
        {
          connection.appendInt32( BOTTLE_TAG_LIST );
          connection.appendInt32( 1 );

          // *** data ***
          connection.appendInt32( BOTTLE_TAG_FLOAT32 );
          connection.appendFloat32( data );
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
        typedef yarp::os::idl::BareStyle< yarp::rosmsg::std_msgs::Float32 >   rosStyle;
        typedef yarp::os::idl::BottleStyle< yarp::rosmsg::std_msgs::Float32 > bottleStyle;

        // The name for this message, ROS will need this
        static constexpr const char* typeName = "std_msgs/Float32";

        // The checksum for this message, ROS will need this
        static constexpr const char* typeChecksum = "73fcbf46b49191e672908e50842a83d4";

        // The source text for this message, ROS will need this
        static constexpr const char* typeText = "\
float32 data\n\
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

#endif // YARP_ROSMSG_std_msgs_Float32_h
