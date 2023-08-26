/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Comm" msg definition:
//   int64 elapsed_time
//   int32 ref_nav1_integer_part
//   int32 ref_nav1_decimal_part
//   int32 nav1_integer_part
//   int32 nav1_decimal_part
//   int64 nav1_elapsed_time
//   int32 ref_nav2_integer_part
//   int32 ref_nav2_decimal_part
//   int32 nav2_integer_part
//   int32 nav2_decimal_part
//   int64 nav2_elapsed_time
//   int32 ref_com1_integer_part
//   int32 ref_com1_decimal_part
//   int32 com1_integer_part
//   int32 com1_decimal_part
//   int64 com1_elapsed_time
//   int32 ref_com2_integer_part
//   int32 ref_com2_decimal_part
//   int32 com2_integer_part
//   int32 com2_decimal_part
//   int64 com2_elapsed_time
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Comm_h
#define YARP_ROSMSG_matb_msgs_Comm_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Comm : public yarp::os::idl::WirePortable
{
public:
    std::int64_t elapsed_time;
    std::int32_t ref_nav1_integer_part;
    std::int32_t ref_nav1_decimal_part;
    std::int32_t nav1_integer_part;
    std::int32_t nav1_decimal_part;
    std::int64_t nav1_elapsed_time;
    std::int32_t ref_nav2_integer_part;
    std::int32_t ref_nav2_decimal_part;
    std::int32_t nav2_integer_part;
    std::int32_t nav2_decimal_part;
    std::int64_t nav2_elapsed_time;
    std::int32_t ref_com1_integer_part;
    std::int32_t ref_com1_decimal_part;
    std::int32_t com1_integer_part;
    std::int32_t com1_decimal_part;
    std::int64_t com1_elapsed_time;
    std::int32_t ref_com2_integer_part;
    std::int32_t ref_com2_decimal_part;
    std::int32_t com2_integer_part;
    std::int32_t com2_decimal_part;
    std::int64_t com2_elapsed_time;

    Comm() :
            elapsed_time(0),
            ref_nav1_integer_part(0),
            ref_nav1_decimal_part(0),
            nav1_integer_part(0),
            nav1_decimal_part(0),
            nav1_elapsed_time(0),
            ref_nav2_integer_part(0),
            ref_nav2_decimal_part(0),
            nav2_integer_part(0),
            nav2_decimal_part(0),
            nav2_elapsed_time(0),
            ref_com1_integer_part(0),
            ref_com1_decimal_part(0),
            com1_integer_part(0),
            com1_decimal_part(0),
            com1_elapsed_time(0),
            ref_com2_integer_part(0),
            ref_com2_decimal_part(0),
            com2_integer_part(0),
            com2_decimal_part(0),
            com2_elapsed_time(0)
    {
    }

    void clear()
    {
        // *** elapsed_time ***
        elapsed_time = 0;

        // *** ref_nav1_integer_part ***
        ref_nav1_integer_part = 0;

        // *** ref_nav1_decimal_part ***
        ref_nav1_decimal_part = 0;

        // *** nav1_integer_part ***
        nav1_integer_part = 0;

        // *** nav1_decimal_part ***
        nav1_decimal_part = 0;

        // *** nav1_elapsed_time ***
        nav1_elapsed_time = 0;

        // *** ref_nav2_integer_part ***
        ref_nav2_integer_part = 0;

        // *** ref_nav2_decimal_part ***
        ref_nav2_decimal_part = 0;

        // *** nav2_integer_part ***
        nav2_integer_part = 0;

        // *** nav2_decimal_part ***
        nav2_decimal_part = 0;

        // *** nav2_elapsed_time ***
        nav2_elapsed_time = 0;

        // *** ref_com1_integer_part ***
        ref_com1_integer_part = 0;

        // *** ref_com1_decimal_part ***
        ref_com1_decimal_part = 0;

        // *** com1_integer_part ***
        com1_integer_part = 0;

        // *** com1_decimal_part ***
        com1_decimal_part = 0;

        // *** com1_elapsed_time ***
        com1_elapsed_time = 0;

        // *** ref_com2_integer_part ***
        ref_com2_integer_part = 0;

        // *** ref_com2_decimal_part ***
        ref_com2_decimal_part = 0;

        // *** com2_integer_part ***
        com2_integer_part = 0;

        // *** com2_decimal_part ***
        com2_decimal_part = 0;

        // *** com2_elapsed_time ***
        com2_elapsed_time = 0;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** elapsed_time ***
        elapsed_time = connection.expectInt64();

        // *** ref_nav1_integer_part ***
        ref_nav1_integer_part = connection.expectInt32();

        // *** ref_nav1_decimal_part ***
        ref_nav1_decimal_part = connection.expectInt32();

        // *** nav1_integer_part ***
        nav1_integer_part = connection.expectInt32();

        // *** nav1_decimal_part ***
        nav1_decimal_part = connection.expectInt32();

        // *** nav1_elapsed_time ***
        nav1_elapsed_time = connection.expectInt64();

        // *** ref_nav2_integer_part ***
        ref_nav2_integer_part = connection.expectInt32();

        // *** ref_nav2_decimal_part ***
        ref_nav2_decimal_part = connection.expectInt32();

        // *** nav2_integer_part ***
        nav2_integer_part = connection.expectInt32();

        // *** nav2_decimal_part ***
        nav2_decimal_part = connection.expectInt32();

        // *** nav2_elapsed_time ***
        nav2_elapsed_time = connection.expectInt64();

        // *** ref_com1_integer_part ***
        ref_com1_integer_part = connection.expectInt32();

        // *** ref_com1_decimal_part ***
        ref_com1_decimal_part = connection.expectInt32();

        // *** com1_integer_part ***
        com1_integer_part = connection.expectInt32();

        // *** com1_decimal_part ***
        com1_decimal_part = connection.expectInt32();

        // *** com1_elapsed_time ***
        com1_elapsed_time = connection.expectInt64();

        // *** ref_com2_integer_part ***
        ref_com2_integer_part = connection.expectInt32();

        // *** ref_com2_decimal_part ***
        ref_com2_decimal_part = connection.expectInt32();

        // *** com2_integer_part ***
        com2_integer_part = connection.expectInt32();

        // *** com2_decimal_part ***
        com2_decimal_part = connection.expectInt32();

        // *** com2_elapsed_time ***
        com2_elapsed_time = connection.expectInt64();

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(21)) {
            return false;
        }

        // *** elapsed_time ***
        elapsed_time = reader.expectInt64();

        // *** ref_nav1_integer_part ***
        ref_nav1_integer_part = reader.expectInt32();

        // *** ref_nav1_decimal_part ***
        ref_nav1_decimal_part = reader.expectInt32();

        // *** nav1_integer_part ***
        nav1_integer_part = reader.expectInt32();

        // *** nav1_decimal_part ***
        nav1_decimal_part = reader.expectInt32();

        // *** nav1_elapsed_time ***
        nav1_elapsed_time = reader.expectInt64();

        // *** ref_nav2_integer_part ***
        ref_nav2_integer_part = reader.expectInt32();

        // *** ref_nav2_decimal_part ***
        ref_nav2_decimal_part = reader.expectInt32();

        // *** nav2_integer_part ***
        nav2_integer_part = reader.expectInt32();

        // *** nav2_decimal_part ***
        nav2_decimal_part = reader.expectInt32();

        // *** nav2_elapsed_time ***
        nav2_elapsed_time = reader.expectInt64();

        // *** ref_com1_integer_part ***
        ref_com1_integer_part = reader.expectInt32();

        // *** ref_com1_decimal_part ***
        ref_com1_decimal_part = reader.expectInt32();

        // *** com1_integer_part ***
        com1_integer_part = reader.expectInt32();

        // *** com1_decimal_part ***
        com1_decimal_part = reader.expectInt32();

        // *** com1_elapsed_time ***
        com1_elapsed_time = reader.expectInt64();

        // *** ref_com2_integer_part ***
        ref_com2_integer_part = reader.expectInt32();

        // *** ref_com2_decimal_part ***
        ref_com2_decimal_part = reader.expectInt32();

        // *** com2_integer_part ***
        com2_integer_part = reader.expectInt32();

        // *** com2_decimal_part ***
        com2_decimal_part = reader.expectInt32();

        // *** com2_elapsed_time ***
        com2_elapsed_time = reader.expectInt64();

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

        // *** ref_nav1_integer_part ***
        connection.appendInt32(ref_nav1_integer_part);

        // *** ref_nav1_decimal_part ***
        connection.appendInt32(ref_nav1_decimal_part);

        // *** nav1_integer_part ***
        connection.appendInt32(nav1_integer_part);

        // *** nav1_decimal_part ***
        connection.appendInt32(nav1_decimal_part);

        // *** nav1_elapsed_time ***
        connection.appendInt64(nav1_elapsed_time);

        // *** ref_nav2_integer_part ***
        connection.appendInt32(ref_nav2_integer_part);

        // *** ref_nav2_decimal_part ***
        connection.appendInt32(ref_nav2_decimal_part);

        // *** nav2_integer_part ***
        connection.appendInt32(nav2_integer_part);

        // *** nav2_decimal_part ***
        connection.appendInt32(nav2_decimal_part);

        // *** nav2_elapsed_time ***
        connection.appendInt64(nav2_elapsed_time);

        // *** ref_com1_integer_part ***
        connection.appendInt32(ref_com1_integer_part);

        // *** ref_com1_decimal_part ***
        connection.appendInt32(ref_com1_decimal_part);

        // *** com1_integer_part ***
        connection.appendInt32(com1_integer_part);

        // *** com1_decimal_part ***
        connection.appendInt32(com1_decimal_part);

        // *** com1_elapsed_time ***
        connection.appendInt64(com1_elapsed_time);

        // *** ref_com2_integer_part ***
        connection.appendInt32(ref_com2_integer_part);

        // *** ref_com2_decimal_part ***
        connection.appendInt32(ref_com2_decimal_part);

        // *** com2_integer_part ***
        connection.appendInt32(com2_integer_part);

        // *** com2_decimal_part ***
        connection.appendInt32(com2_decimal_part);

        // *** com2_elapsed_time ***
        connection.appendInt64(com2_elapsed_time);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(21);

        // *** elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(elapsed_time);

        // *** ref_nav1_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_nav1_integer_part);

        // *** ref_nav1_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_nav1_decimal_part);

        // *** nav1_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(nav1_integer_part);

        // *** nav1_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(nav1_decimal_part);

        // *** nav1_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(nav1_elapsed_time);

        // *** ref_nav2_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_nav2_integer_part);

        // *** ref_nav2_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_nav2_decimal_part);

        // *** nav2_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(nav2_integer_part);

        // *** nav2_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(nav2_decimal_part);

        // *** nav2_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(nav2_elapsed_time);

        // *** ref_com1_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_com1_integer_part);

        // *** ref_com1_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_com1_decimal_part);

        // *** com1_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(com1_integer_part);

        // *** com1_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(com1_decimal_part);

        // *** com1_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(com1_elapsed_time);

        // *** ref_com2_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_com2_integer_part);

        // *** ref_com2_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(ref_com2_decimal_part);

        // *** com2_integer_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(com2_integer_part);

        // *** com2_decimal_part ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(com2_decimal_part);

        // *** com2_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(com2_elapsed_time);

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Comm> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Comm> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Comm";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "ddc4610023a58ad1beae7d6c9d70e31e";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
int64 elapsed_time\n\
int32 ref_nav1_integer_part\n\
int32 ref_nav1_decimal_part\n\
int32 nav1_integer_part\n\
int32 nav1_decimal_part\n\
int64 nav1_elapsed_time\n\
int32 ref_nav2_integer_part\n\
int32 ref_nav2_decimal_part\n\
int32 nav2_integer_part\n\
int32 nav2_decimal_part\n\
int64 nav2_elapsed_time\n\
int32 ref_com1_integer_part\n\
int32 ref_com1_decimal_part\n\
int32 com1_integer_part\n\
int32 com1_decimal_part\n\
int64 com1_elapsed_time\n\
int32 ref_com2_integer_part\n\
int32 ref_com2_decimal_part\n\
int32 com2_integer_part\n\
int32 com2_decimal_part\n\
int64 com2_elapsed_time\n\
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

#endif // YARP_ROSMSG_matb_msgs_Comm_h
