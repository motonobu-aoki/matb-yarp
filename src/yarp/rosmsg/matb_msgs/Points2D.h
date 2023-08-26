/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Points2D" msg definition:
//   Point2D[] point
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Points2D_h
#define YARP_ROSMSG_matb_msgs_Points2D_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>
#include <yarp/rosmsg/matb_msgs/Point2D.h>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Points2D : public yarp::os::idl::WirePortable
{
public:
    std::vector<yarp::rosmsg::matb_msgs::Point2D> point;

    Points2D() :
            point()
    {
    }

    void clear()
    {
        // *** point ***
        point.clear();
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** point ***
        int len = connection.expectInt32();
        point.resize(len);
        for (int i=0; i<len; i++) {
            if (!point[i].read(connection)) {
                return false;
            }
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(1)) {
            return false;
        }

        // *** point ***
        if (connection.expectInt32() != BOTTLE_TAG_LIST) {
            return false;
        }
        int len = connection.expectInt32();
        point.resize(len);
        for (int i=0; i<len; i++) {
            if (!point[i].read(connection)) {
                return false;
            }
        }

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
        // *** point ***
        connection.appendInt32(point.size());
        for (size_t i=0; i<point.size(); i++) {
            if (!point[i].write(connection)) {
                return false;
            }
        }

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(1);

        // *** point ***
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(point.size());
        for (size_t i=0; i<point.size(); i++) {
            if (!point[i].write(connection)) {
                return false;
            }
        }

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Points2D> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Points2D> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Points2D";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "e3b774b4dbf00429835dbf2ea05f390b";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
Point2D[] point\n\
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

#endif // YARP_ROSMSG_matb_msgs_Points2D_h
