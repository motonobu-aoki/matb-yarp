/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Sysmon" msg definition:
//   int64 elapsed_time
//   
//   int32 base_position_f1
//   int32 position_f1
//   int64 f1_elapsed_time
//   
//   int32 base_position_f2
//   int32 position_f2
//   int64 f2_elapsed_time
//   
//   int32 base_position_f3
//   int32 position_f3
//   int64 f3_elapsed_time
//   
//   int32 base_position_f4
//   int32 position_f4
//   int64 f4_elapsed_time
//   
//   bool is_green
//   int64 f5_elapsed_time
//   
//   bool is_red
//   int64 f6_elapsed_time
//   
//   string pressed_key
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Sysmon_h
#define YARP_ROSMSG_matb_msgs_Sysmon_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Sysmon : public yarp::os::idl::WirePortable
{
public:
    std::int64_t elapsed_time;
    std::int32_t base_position_f1;
    std::int32_t position_f1;
    std::int64_t f1_elapsed_time;
    std::int32_t base_position_f2;
    std::int32_t position_f2;
    std::int64_t f2_elapsed_time;
    std::int32_t base_position_f3;
    std::int32_t position_f3;
    std::int64_t f3_elapsed_time;
    std::int32_t base_position_f4;
    std::int32_t position_f4;
    std::int64_t f4_elapsed_time;
    bool is_green;
    std::int64_t f5_elapsed_time;
    bool is_red;
    std::int64_t f6_elapsed_time;
    std::string pressed_key;

    Sysmon() :
            elapsed_time(0),
            base_position_f1(0),
            position_f1(0),
            f1_elapsed_time(0),
            base_position_f2(0),
            position_f2(0),
            f2_elapsed_time(0),
            base_position_f3(0),
            position_f3(0),
            f3_elapsed_time(0),
            base_position_f4(0),
            position_f4(0),
            f4_elapsed_time(0),
            is_green(false),
            f5_elapsed_time(0),
            is_red(false),
            f6_elapsed_time(0),
            pressed_key("")
    {
    }

    void clear()
    {
        // *** elapsed_time ***
        elapsed_time = 0;

        // *** base_position_f1 ***
        base_position_f1 = 0;

        // *** position_f1 ***
        position_f1 = 0;

        // *** f1_elapsed_time ***
        f1_elapsed_time = 0;

        // *** base_position_f2 ***
        base_position_f2 = 0;

        // *** position_f2 ***
        position_f2 = 0;

        // *** f2_elapsed_time ***
        f2_elapsed_time = 0;

        // *** base_position_f3 ***
        base_position_f3 = 0;

        // *** position_f3 ***
        position_f3 = 0;

        // *** f3_elapsed_time ***
        f3_elapsed_time = 0;

        // *** base_position_f4 ***
        base_position_f4 = 0;

        // *** position_f4 ***
        position_f4 = 0;

        // *** f4_elapsed_time ***
        f4_elapsed_time = 0;

        // *** is_green ***
        is_green = false;

        // *** f5_elapsed_time ***
        f5_elapsed_time = 0;

        // *** is_red ***
        is_red = false;

        // *** f6_elapsed_time ***
        f6_elapsed_time = 0;

        // *** pressed_key ***
        pressed_key = "";
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** elapsed_time ***
        elapsed_time = connection.expectInt64();

        // *** base_position_f1 ***
        base_position_f1 = connection.expectInt32();

        // *** position_f1 ***
        position_f1 = connection.expectInt32();

        // *** f1_elapsed_time ***
        f1_elapsed_time = connection.expectInt64();

        // *** base_position_f2 ***
        base_position_f2 = connection.expectInt32();

        // *** position_f2 ***
        position_f2 = connection.expectInt32();

        // *** f2_elapsed_time ***
        f2_elapsed_time = connection.expectInt64();

        // *** base_position_f3 ***
        base_position_f3 = connection.expectInt32();

        // *** position_f3 ***
        position_f3 = connection.expectInt32();

        // *** f3_elapsed_time ***
        f3_elapsed_time = connection.expectInt64();

        // *** base_position_f4 ***
        base_position_f4 = connection.expectInt32();

        // *** position_f4 ***
        position_f4 = connection.expectInt32();

        // *** f4_elapsed_time ***
        f4_elapsed_time = connection.expectInt64();

        // *** is_green ***
        if (!connection.expectBlock((char*)&is_green, 1)) {
            return false;
        }

        // *** f5_elapsed_time ***
        f5_elapsed_time = connection.expectInt64();

        // *** is_red ***
        if (!connection.expectBlock((char*)&is_red, 1)) {
            return false;
        }

        // *** f6_elapsed_time ***
        f6_elapsed_time = connection.expectInt64();

        // *** pressed_key ***
        int len = connection.expectInt32();
        pressed_key.resize(len);
        if (!connection.expectBlock((char*)pressed_key.c_str(), len)) {
            return false;
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(18)) {
            return false;
        }

        // *** elapsed_time ***
        elapsed_time = reader.expectInt64();

        // *** base_position_f1 ***
        base_position_f1 = reader.expectInt32();

        // *** position_f1 ***
        position_f1 = reader.expectInt32();

        // *** f1_elapsed_time ***
        f1_elapsed_time = reader.expectInt64();

        // *** base_position_f2 ***
        base_position_f2 = reader.expectInt32();

        // *** position_f2 ***
        position_f2 = reader.expectInt32();

        // *** f2_elapsed_time ***
        f2_elapsed_time = reader.expectInt64();

        // *** base_position_f3 ***
        base_position_f3 = reader.expectInt32();

        // *** position_f3 ***
        position_f3 = reader.expectInt32();

        // *** f3_elapsed_time ***
        f3_elapsed_time = reader.expectInt64();

        // *** base_position_f4 ***
        base_position_f4 = reader.expectInt32();

        // *** position_f4 ***
        position_f4 = reader.expectInt32();

        // *** f4_elapsed_time ***
        f4_elapsed_time = reader.expectInt64();

        // *** is_green ***
        is_green = reader.expectInt8();

        // *** f5_elapsed_time ***
        f5_elapsed_time = reader.expectInt64();

        // *** is_red ***
        is_red = reader.expectInt8();

        // *** f6_elapsed_time ***
        f6_elapsed_time = reader.expectInt64();

        // *** pressed_key ***
        if (!reader.readString(pressed_key)) {
            return false;
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
        // *** elapsed_time ***
        connection.appendInt64(elapsed_time);

        // *** base_position_f1 ***
        connection.appendInt32(base_position_f1);

        // *** position_f1 ***
        connection.appendInt32(position_f1);

        // *** f1_elapsed_time ***
        connection.appendInt64(f1_elapsed_time);

        // *** base_position_f2 ***
        connection.appendInt32(base_position_f2);

        // *** position_f2 ***
        connection.appendInt32(position_f2);

        // *** f2_elapsed_time ***
        connection.appendInt64(f2_elapsed_time);

        // *** base_position_f3 ***
        connection.appendInt32(base_position_f3);

        // *** position_f3 ***
        connection.appendInt32(position_f3);

        // *** f3_elapsed_time ***
        connection.appendInt64(f3_elapsed_time);

        // *** base_position_f4 ***
        connection.appendInt32(base_position_f4);

        // *** position_f4 ***
        connection.appendInt32(position_f4);

        // *** f4_elapsed_time ***
        connection.appendInt64(f4_elapsed_time);

        // *** is_green ***
        connection.appendBlock((char*)&is_green, 1);

        // *** f5_elapsed_time ***
        connection.appendInt64(f5_elapsed_time);

        // *** is_red ***
        connection.appendBlock((char*)&is_red, 1);

        // *** f6_elapsed_time ***
        connection.appendInt64(f6_elapsed_time);

        // *** pressed_key ***
        connection.appendInt32(pressed_key.length());
        connection.appendExternalBlock((char*)pressed_key.c_str(), pressed_key.length());

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(18);

        // *** elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(elapsed_time);

        // *** base_position_f1 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(base_position_f1);

        // *** position_f1 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(position_f1);

        // *** f1_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f1_elapsed_time);

        // *** base_position_f2 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(base_position_f2);

        // *** position_f2 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(position_f2);

        // *** f2_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f2_elapsed_time);

        // *** base_position_f3 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(base_position_f3);

        // *** position_f3 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(position_f3);

        // *** f3_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f3_elapsed_time);

        // *** base_position_f4 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(base_position_f4);

        // *** position_f4 ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(position_f4);

        // *** f4_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f4_elapsed_time);

        // *** is_green ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(is_green);

        // *** f5_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f5_elapsed_time);

        // *** is_red ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(is_red);

        // *** f6_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(f6_elapsed_time);

        // *** pressed_key ***
        connection.appendInt32(BOTTLE_TAG_STRING);
        connection.appendInt32(pressed_key.length());
        connection.appendExternalBlock((char*)pressed_key.c_str(), pressed_key.length());

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Sysmon> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Sysmon> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Sysmon";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "d4ecf11b30e277e6362791713a295d4f";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
int64 elapsed_time\n\
\n\
int32 base_position_f1\n\
int32 position_f1\n\
int64 f1_elapsed_time\n\
\n\
int32 base_position_f2\n\
int32 position_f2\n\
int64 f2_elapsed_time\n\
\n\
int32 base_position_f3\n\
int32 position_f3\n\
int64 f3_elapsed_time\n\
\n\
int32 base_position_f4\n\
int32 position_f4\n\
int64 f4_elapsed_time\n\
\n\
bool is_green\n\
int64 f5_elapsed_time\n\
\n\
bool is_red\n\
int64 f6_elapsed_time\n\
\n\
string pressed_key\n\
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

#endif // YARP_ROSMSG_matb_msgs_Sysmon_h
