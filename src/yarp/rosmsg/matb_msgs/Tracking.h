/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Tracking" msg definition:
//   int64 elapsed_time
//   matb_msgs/Point2D point
//   int64 out_of_track_elapsed_time
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Tracking_h
#define YARP_ROSMSG_matb_msgs_Tracking_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/matb_msgs/Point2D.h>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Tracking : public yarp::os::idl::WirePortable
{
public:
    std::int64_t elapsed_time;
    yarp::rosmsg::matb_msgs::Point2D point;
    std::int64_t out_of_track_elapsed_time;

    Tracking() :
            elapsed_time(0),
            point(),
            out_of_track_elapsed_time(0)
    {
    }

    void clear()
    {
        // *** elapsed_time ***
        elapsed_time = 0;

        // *** point ***
        point.clear();

        // *** out_of_track_elapsed_time ***
        out_of_track_elapsed_time = 0;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** elapsed_time ***
        elapsed_time = connection.expectInt64();

        // *** point ***
        if (!point.read(connection)) {
            return false;
        }

        // *** out_of_track_elapsed_time ***
        out_of_track_elapsed_time = connection.expectInt64();

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(3)) {
            return false;
        }

        // *** elapsed_time ***
        elapsed_time = reader.expectInt64();

        // *** point ***
        if (!point.read(connection)) {
            return false;
        }

        // *** out_of_track_elapsed_time ***
        out_of_track_elapsed_time = reader.expectInt64();

        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::read;
    bool read(yarp::os::ConnectionReader& connection) override
    {
        return (connection.isBareMode() ? readBare(connection)
                                        : readBottle(connection));
    }

    bool writeBare(yarp::os::ConnectionWriter& connection) const override
    {
        // *** elapsed_time ***
        connection.appendInt64(elapsed_time);

        // *** point ***
        if (!point.write(connection)) {
            return false;
        }

        // *** out_of_track_elapsed_time ***
        connection.appendInt64(out_of_track_elapsed_time);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(3);

        // *** elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(elapsed_time);

        // *** point ***
        if (!point.write(connection)) {
            return false;
        }

        // *** out_of_track_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(out_of_track_elapsed_time);

        connection.convertTextMode();
        return !connection.isError();
    }

    using yarp::os::idl::WirePortable::write;
    bool write(yarp::os::ConnectionWriter& connection) const override
    {
        return (connection.isBareMode() ? writeBare(connection)
                                        : writeBottle(connection));
    }

    // This class will serialize ROS style or YARP style depending on protocol.
    // If you need to force a serialization style, use one of these classes:
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Tracking> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Tracking> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Tracking";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "67da2eae3a16360b24c3a6262b8c08c1";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
int64 elapsed_time\n\
matb_msgs/Point2D point\n\
int64 out_of_track_elapsed_time\n\
\n\
\n\
================================================================================\n\
MSG: matb_msgs/Point2D\n\
float64 x\n\
float64 y\n\
\n\
\n\
";

    yarp::os::Type getType() const override
    {
        yarp::os::Type typ = yarp::os::Type::byName(typeName, typeName);
        typ.addProperty("md5sum", yarp::os::Value(typeChecksum));
        typ.addProperty("message_definition", yarp::os::Value(typeText));
        return typ;
    }
};

} // namespace matb_msgs
} // namespace rosmsg
} // namespace yarp

#endif // YARP_ROSMSG_matb_msgs_Tracking_h
