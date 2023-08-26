/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Resman" msg definition:
//   int64 elapsed_time
//   int32 amount_of_tank_A
//   int64 tank_A_elapsed_time
//   int32 amount_of_tank_B
//   int64 tank_B_elapsed_time
//   int32 amount_of_tank_C
//   int32 amount_of_tank_D
//   bool valve_1_is_on
//   bool valve_2_is_on
//   bool valve_3_is_on
//   bool valve_4_is_on
//   bool valve_5_is_on
//   bool valve_6_is_on
//   bool valve_7_is_on
//   bool valve_8_is_on
//   bool valve_1_is_failed
//   bool valve_2_is_failed
//   bool valve_3_is_failed
//   bool valve_4_is_failed
//   bool valve_5_is_failed
//   bool valve_6_is_failed
//   bool valve_7_is_failed
//   bool valve_8_is_failed
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Resman_h
#define YARP_ROSMSG_matb_msgs_Resman_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Resman : public yarp::os::idl::WirePortable
{
public:
    std::int64_t elapsed_time;
    std::int32_t amount_of_tank_A;
    std::int64_t tank_A_elapsed_time;
    std::int32_t amount_of_tank_B;
    std::int64_t tank_B_elapsed_time;
    std::int32_t amount_of_tank_C;
    std::int32_t amount_of_tank_D;
    bool valve_1_is_on;
    bool valve_2_is_on;
    bool valve_3_is_on;
    bool valve_4_is_on;
    bool valve_5_is_on;
    bool valve_6_is_on;
    bool valve_7_is_on;
    bool valve_8_is_on;
    bool valve_1_is_failed;
    bool valve_2_is_failed;
    bool valve_3_is_failed;
    bool valve_4_is_failed;
    bool valve_5_is_failed;
    bool valve_6_is_failed;
    bool valve_7_is_failed;
    bool valve_8_is_failed;

    Resman() :
            elapsed_time(0),
            amount_of_tank_A(0),
            tank_A_elapsed_time(0),
            amount_of_tank_B(0),
            tank_B_elapsed_time(0),
            amount_of_tank_C(0),
            amount_of_tank_D(0),
            valve_1_is_on(false),
            valve_2_is_on(false),
            valve_3_is_on(false),
            valve_4_is_on(false),
            valve_5_is_on(false),
            valve_6_is_on(false),
            valve_7_is_on(false),
            valve_8_is_on(false),
            valve_1_is_failed(false),
            valve_2_is_failed(false),
            valve_3_is_failed(false),
            valve_4_is_failed(false),
            valve_5_is_failed(false),
            valve_6_is_failed(false),
            valve_7_is_failed(false),
            valve_8_is_failed(false)
    {
    }

    void clear()
    {
        // *** elapsed_time ***
        elapsed_time = 0;

        // *** amount_of_tank_A ***
        amount_of_tank_A = 0;

        // *** tank_A_elapsed_time ***
        tank_A_elapsed_time = 0;

        // *** amount_of_tank_B ***
        amount_of_tank_B = 0;

        // *** tank_B_elapsed_time ***
        tank_B_elapsed_time = 0;

        // *** amount_of_tank_C ***
        amount_of_tank_C = 0;

        // *** amount_of_tank_D ***
        amount_of_tank_D = 0;

        // *** valve_1_is_on ***
        valve_1_is_on = false;

        // *** valve_2_is_on ***
        valve_2_is_on = false;

        // *** valve_3_is_on ***
        valve_3_is_on = false;

        // *** valve_4_is_on ***
        valve_4_is_on = false;

        // *** valve_5_is_on ***
        valve_5_is_on = false;

        // *** valve_6_is_on ***
        valve_6_is_on = false;

        // *** valve_7_is_on ***
        valve_7_is_on = false;

        // *** valve_8_is_on ***
        valve_8_is_on = false;

        // *** valve_1_is_failed ***
        valve_1_is_failed = false;

        // *** valve_2_is_failed ***
        valve_2_is_failed = false;

        // *** valve_3_is_failed ***
        valve_3_is_failed = false;

        // *** valve_4_is_failed ***
        valve_4_is_failed = false;

        // *** valve_5_is_failed ***
        valve_5_is_failed = false;

        // *** valve_6_is_failed ***
        valve_6_is_failed = false;

        // *** valve_7_is_failed ***
        valve_7_is_failed = false;

        // *** valve_8_is_failed ***
        valve_8_is_failed = false;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** elapsed_time ***
        elapsed_time = connection.expectInt64();

        // *** amount_of_tank_A ***
        amount_of_tank_A = connection.expectInt32();

        // *** tank_A_elapsed_time ***
        tank_A_elapsed_time = connection.expectInt64();

        // *** amount_of_tank_B ***
        amount_of_tank_B = connection.expectInt32();

        // *** tank_B_elapsed_time ***
        tank_B_elapsed_time = connection.expectInt64();

        // *** amount_of_tank_C ***
        amount_of_tank_C = connection.expectInt32();

        // *** amount_of_tank_D ***
        amount_of_tank_D = connection.expectInt32();

        // *** valve_1_is_on ***
        if (!connection.expectBlock((char*)&valve_1_is_on, 1)) {
            return false;
        }

        // *** valve_2_is_on ***
        if (!connection.expectBlock((char*)&valve_2_is_on, 1)) {
            return false;
        }

        // *** valve_3_is_on ***
        if (!connection.expectBlock((char*)&valve_3_is_on, 1)) {
            return false;
        }

        // *** valve_4_is_on ***
        if (!connection.expectBlock((char*)&valve_4_is_on, 1)) {
            return false;
        }

        // *** valve_5_is_on ***
        if (!connection.expectBlock((char*)&valve_5_is_on, 1)) {
            return false;
        }

        // *** valve_6_is_on ***
        if (!connection.expectBlock((char*)&valve_6_is_on, 1)) {
            return false;
        }

        // *** valve_7_is_on ***
        if (!connection.expectBlock((char*)&valve_7_is_on, 1)) {
            return false;
        }

        // *** valve_8_is_on ***
        if (!connection.expectBlock((char*)&valve_8_is_on, 1)) {
            return false;
        }

        // *** valve_1_is_failed ***
        if (!connection.expectBlock((char*)&valve_1_is_failed, 1)) {
            return false;
        }

        // *** valve_2_is_failed ***
        if (!connection.expectBlock((char*)&valve_2_is_failed, 1)) {
            return false;
        }

        // *** valve_3_is_failed ***
        if (!connection.expectBlock((char*)&valve_3_is_failed, 1)) {
            return false;
        }

        // *** valve_4_is_failed ***
        if (!connection.expectBlock((char*)&valve_4_is_failed, 1)) {
            return false;
        }

        // *** valve_5_is_failed ***
        if (!connection.expectBlock((char*)&valve_5_is_failed, 1)) {
            return false;
        }

        // *** valve_6_is_failed ***
        if (!connection.expectBlock((char*)&valve_6_is_failed, 1)) {
            return false;
        }

        // *** valve_7_is_failed ***
        if (!connection.expectBlock((char*)&valve_7_is_failed, 1)) {
            return false;
        }

        // *** valve_8_is_failed ***
        if (!connection.expectBlock((char*)&valve_8_is_failed, 1)) {
            return false;
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(23)) {
            return false;
        }

        // *** elapsed_time ***
        elapsed_time = reader.expectInt64();

        // *** amount_of_tank_A ***
        amount_of_tank_A = reader.expectInt32();

        // *** tank_A_elapsed_time ***
        tank_A_elapsed_time = reader.expectInt64();

        // *** amount_of_tank_B ***
        amount_of_tank_B = reader.expectInt32();

        // *** tank_B_elapsed_time ***
        tank_B_elapsed_time = reader.expectInt64();

        // *** amount_of_tank_C ***
        amount_of_tank_C = reader.expectInt32();

        // *** amount_of_tank_D ***
        amount_of_tank_D = reader.expectInt32();

        // *** valve_1_is_on ***
        valve_1_is_on = reader.expectInt8();

        // *** valve_2_is_on ***
        valve_2_is_on = reader.expectInt8();

        // *** valve_3_is_on ***
        valve_3_is_on = reader.expectInt8();

        // *** valve_4_is_on ***
        valve_4_is_on = reader.expectInt8();

        // *** valve_5_is_on ***
        valve_5_is_on = reader.expectInt8();

        // *** valve_6_is_on ***
        valve_6_is_on = reader.expectInt8();

        // *** valve_7_is_on ***
        valve_7_is_on = reader.expectInt8();

        // *** valve_8_is_on ***
        valve_8_is_on = reader.expectInt8();

        // *** valve_1_is_failed ***
        valve_1_is_failed = reader.expectInt8();

        // *** valve_2_is_failed ***
        valve_2_is_failed = reader.expectInt8();

        // *** valve_3_is_failed ***
        valve_3_is_failed = reader.expectInt8();

        // *** valve_4_is_failed ***
        valve_4_is_failed = reader.expectInt8();

        // *** valve_5_is_failed ***
        valve_5_is_failed = reader.expectInt8();

        // *** valve_6_is_failed ***
        valve_6_is_failed = reader.expectInt8();

        // *** valve_7_is_failed ***
        valve_7_is_failed = reader.expectInt8();

        // *** valve_8_is_failed ***
        valve_8_is_failed = reader.expectInt8();

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

        // *** amount_of_tank_A ***
        connection.appendInt32(amount_of_tank_A);

        // *** tank_A_elapsed_time ***
        connection.appendInt64(tank_A_elapsed_time);

        // *** amount_of_tank_B ***
        connection.appendInt32(amount_of_tank_B);

        // *** tank_B_elapsed_time ***
        connection.appendInt64(tank_B_elapsed_time);

        // *** amount_of_tank_C ***
        connection.appendInt32(amount_of_tank_C);

        // *** amount_of_tank_D ***
        connection.appendInt32(amount_of_tank_D);

        // *** valve_1_is_on ***
        connection.appendBlock((char*)&valve_1_is_on, 1);

        // *** valve_2_is_on ***
        connection.appendBlock((char*)&valve_2_is_on, 1);

        // *** valve_3_is_on ***
        connection.appendBlock((char*)&valve_3_is_on, 1);

        // *** valve_4_is_on ***
        connection.appendBlock((char*)&valve_4_is_on, 1);

        // *** valve_5_is_on ***
        connection.appendBlock((char*)&valve_5_is_on, 1);

        // *** valve_6_is_on ***
        connection.appendBlock((char*)&valve_6_is_on, 1);

        // *** valve_7_is_on ***
        connection.appendBlock((char*)&valve_7_is_on, 1);

        // *** valve_8_is_on ***
        connection.appendBlock((char*)&valve_8_is_on, 1);

        // *** valve_1_is_failed ***
        connection.appendBlock((char*)&valve_1_is_failed, 1);

        // *** valve_2_is_failed ***
        connection.appendBlock((char*)&valve_2_is_failed, 1);

        // *** valve_3_is_failed ***
        connection.appendBlock((char*)&valve_3_is_failed, 1);

        // *** valve_4_is_failed ***
        connection.appendBlock((char*)&valve_4_is_failed, 1);

        // *** valve_5_is_failed ***
        connection.appendBlock((char*)&valve_5_is_failed, 1);

        // *** valve_6_is_failed ***
        connection.appendBlock((char*)&valve_6_is_failed, 1);

        // *** valve_7_is_failed ***
        connection.appendBlock((char*)&valve_7_is_failed, 1);

        // *** valve_8_is_failed ***
        connection.appendBlock((char*)&valve_8_is_failed, 1);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(23);

        // *** elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(elapsed_time);

        // *** amount_of_tank_A ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(amount_of_tank_A);

        // *** tank_A_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(tank_A_elapsed_time);

        // *** amount_of_tank_B ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(amount_of_tank_B);

        // *** tank_B_elapsed_time ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(tank_B_elapsed_time);

        // *** amount_of_tank_C ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(amount_of_tank_C);

        // *** amount_of_tank_D ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(amount_of_tank_D);

        // *** valve_1_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_1_is_on);

        // *** valve_2_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_2_is_on);

        // *** valve_3_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_3_is_on);

        // *** valve_4_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_4_is_on);

        // *** valve_5_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_5_is_on);

        // *** valve_6_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_6_is_on);

        // *** valve_7_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_7_is_on);

        // *** valve_8_is_on ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_8_is_on);

        // *** valve_1_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_1_is_failed);

        // *** valve_2_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_2_is_failed);

        // *** valve_3_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_3_is_failed);

        // *** valve_4_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_4_is_failed);

        // *** valve_5_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_5_is_failed);

        // *** valve_6_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_6_is_failed);

        // *** valve_7_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_7_is_failed);

        // *** valve_8_is_failed ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(valve_8_is_failed);

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Resman> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Resman> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Resman";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "da3676e983524b94ba2018ad065bedea";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
int64 elapsed_time\n\
int32 amount_of_tank_A\n\
int64 tank_A_elapsed_time\n\
int32 amount_of_tank_B\n\
int64 tank_B_elapsed_time\n\
int32 amount_of_tank_C\n\
int32 amount_of_tank_D\n\
bool valve_1_is_on\n\
bool valve_2_is_on\n\
bool valve_3_is_on\n\
bool valve_4_is_on\n\
bool valve_5_is_on\n\
bool valve_6_is_on\n\
bool valve_7_is_on\n\
bool valve_8_is_on\n\
bool valve_1_is_failed\n\
bool valve_2_is_failed\n\
bool valve_3_is_failed\n\
bool valve_4_is_failed\n\
bool valve_5_is_failed\n\
bool valve_6_is_failed\n\
bool valve_7_is_failed\n\
bool valve_8_is_failed\n\
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

#endif // YARP_ROSMSG_matb_msgs_Resman_h
