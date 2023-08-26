/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/QKey" msg definition:
//   int64 timestamp
//   string text
//   int32 count
//   int32 key
//   int32 type
//   int32 modifiers
//   int32 native_modifiers
//   int32 native_scan_code
//   int32 native_virtual_key
//   bool is_auto_repeat
//   bool is_accepted
//   bool spontaneous
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_QKey_h
#define YARP_ROSMSG_matb_msgs_QKey_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class QKey : public yarp::os::idl::WirePortable
{
public:
    std::int64_t timestamp;
    std::string text;
    std::int32_t count;
    std::int32_t key;
    std::int32_t type;
    std::int32_t modifiers;
    std::int32_t native_modifiers;
    std::int32_t native_scan_code;
    std::int32_t native_virtual_key;
    bool is_auto_repeat;
    bool is_accepted;
    bool spontaneous;

    QKey() :
            timestamp(0),
            text(""),
            count(0),
            key(0),
            type(0),
            modifiers(0),
            native_modifiers(0),
            native_scan_code(0),
            native_virtual_key(0),
            is_auto_repeat(false),
            is_accepted(false),
            spontaneous(false)
    {
    }

    void clear()
    {
        // *** timestamp ***
        timestamp = 0;

        // *** text ***
        text = "";

        // *** count ***
        count = 0;

        // *** key ***
        key = 0;

        // *** type ***
        type = 0;

        // *** modifiers ***
        modifiers = 0;

        // *** native_modifiers ***
        native_modifiers = 0;

        // *** native_scan_code ***
        native_scan_code = 0;

        // *** native_virtual_key ***
        native_virtual_key = 0;

        // *** is_auto_repeat ***
        is_auto_repeat = false;

        // *** is_accepted ***
        is_accepted = false;

        // *** spontaneous ***
        spontaneous = false;
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** timestamp ***
        timestamp = connection.expectInt64();

        // *** text ***
        int len = connection.expectInt32();
        text.resize(len);
        if (!connection.expectBlock((char*)text.c_str(), len)) {
            return false;
        }

        // *** count ***
        count = connection.expectInt32();

        // *** key ***
        key = connection.expectInt32();

        // *** type ***
        type = connection.expectInt32();

        // *** modifiers ***
        modifiers = connection.expectInt32();

        // *** native_modifiers ***
        native_modifiers = connection.expectInt32();

        // *** native_scan_code ***
        native_scan_code = connection.expectInt32();

        // *** native_virtual_key ***
        native_virtual_key = connection.expectInt32();

        // *** is_auto_repeat ***
        if (!connection.expectBlock((char*)&is_auto_repeat, 1)) {
            return false;
        }

        // *** is_accepted ***
        if (!connection.expectBlock((char*)&is_accepted, 1)) {
            return false;
        }

        // *** spontaneous ***
        if (!connection.expectBlock((char*)&spontaneous, 1)) {
            return false;
        }

        return !connection.isError();
    }

    bool readBottle(yarp::os::ConnectionReader& connection) override
    {
        connection.convertTextMode();
        yarp::os::idl::WireReader reader(connection);
        if (!reader.readListHeader(12)) {
            return false;
        }

        // *** timestamp ***
        timestamp = reader.expectInt64();

        // *** text ***
        if (!reader.readString(text)) {
            return false;
        }

        // *** count ***
        count = reader.expectInt32();

        // *** key ***
        key = reader.expectInt32();

        // *** type ***
        type = reader.expectInt32();

        // *** modifiers ***
        modifiers = reader.expectInt32();

        // *** native_modifiers ***
        native_modifiers = reader.expectInt32();

        // *** native_scan_code ***
        native_scan_code = reader.expectInt32();

        // *** native_virtual_key ***
        native_virtual_key = reader.expectInt32();

        // *** is_auto_repeat ***
        is_auto_repeat = reader.expectInt8();

        // *** is_accepted ***
        is_accepted = reader.expectInt8();

        // *** spontaneous ***
        spontaneous = reader.expectInt8();

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
        // *** timestamp ***
        connection.appendInt64(timestamp);

        // *** text ***
        connection.appendInt32(text.length());
        connection.appendExternalBlock((char*)text.c_str(), text.length());

        // *** count ***
        connection.appendInt32(count);

        // *** key ***
        connection.appendInt32(key);

        // *** type ***
        connection.appendInt32(type);

        // *** modifiers ***
        connection.appendInt32(modifiers);

        // *** native_modifiers ***
        connection.appendInt32(native_modifiers);

        // *** native_scan_code ***
        connection.appendInt32(native_scan_code);

        // *** native_virtual_key ***
        connection.appendInt32(native_virtual_key);

        // *** is_auto_repeat ***
        connection.appendBlock((char*)&is_auto_repeat, 1);

        // *** is_accepted ***
        connection.appendBlock((char*)&is_accepted, 1);

        // *** spontaneous ***
        connection.appendBlock((char*)&spontaneous, 1);

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(12);

        // *** timestamp ***
        connection.appendInt32(BOTTLE_TAG_INT64);
        connection.appendInt64(timestamp);

        // *** text ***
        connection.appendInt32(BOTTLE_TAG_STRING);
        connection.appendInt32(text.length());
        connection.appendExternalBlock((char*)text.c_str(), text.length());

        // *** count ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(count);

        // *** key ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(key);

        // *** type ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(type);

        // *** modifiers ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(modifiers);

        // *** native_modifiers ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(native_modifiers);

        // *** native_scan_code ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(native_scan_code);

        // *** native_virtual_key ***
        connection.appendInt32(BOTTLE_TAG_INT32);
        connection.appendInt32(native_virtual_key);

        // *** is_auto_repeat ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(is_auto_repeat);

        // *** is_accepted ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(is_accepted);

        // *** spontaneous ***
        connection.appendInt32(BOTTLE_TAG_INT8);
        connection.appendInt8(spontaneous);

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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::QKey> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::QKey> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/QKey";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "e20a2b0c536f1092239b5fb983d8ca60";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
int64 timestamp\n\
string text\n\
int32 count\n\
int32 key\n\
int32 type\n\
int32 modifiers\n\
int32 native_modifiers\n\
int32 native_scan_code\n\
int32 native_virtual_key\n\
bool is_auto_repeat\n\
bool is_accepted\n\
bool spontaneous\n\
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

#endif // YARP_ROSMSG_matb_msgs_QKey_h
