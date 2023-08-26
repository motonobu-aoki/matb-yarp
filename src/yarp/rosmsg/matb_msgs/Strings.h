/*
 * Copyright (C) 2006-2020 Istituto Italiano di Tecnologia (IIT)
 * All rights reserved.
 *
 * This software may be modified and distributed under the terms of the
 * BSD-3-Clause license. See the accompanying LICENSE file for details.
 */

// This is an automatically generated file.

// Generated from the following "matb_msgs/Strings" msg definition:
//   string[] data
//   
//   
// Instances of this class can be read and written with YARP ports,
// using a ROS-compatible format.

#ifndef YARP_ROSMSG_matb_msgs_Strings_h
#define YARP_ROSMSG_matb_msgs_Strings_h

#include <yarp/os/Wire.h>
#include <yarp/os/Type.h>
#include <yarp/os/idl/WireTypes.h>
#include <string>
#include <vector>

namespace yarp {
namespace rosmsg {
namespace matb_msgs {

class Strings : public yarp::os::idl::WirePortable
{
public:
    std::vector<std::string> data;

    Strings() :
            data()
    {
    }

    void clear()
    {
        // *** data ***
        data.clear();
    }

    bool readBare(yarp::os::ConnectionReader& connection) override
    {
        // *** data ***
        int len = connection.expectInt32();
        data.resize(len);
        for (int i=0; i<len; i++) {
            int len2 = connection.expectInt32();
            data[i].resize(len2);
            if (!connection.expectBlock((char*)data[i].c_str(), len2)) {
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

        // *** data ***
        if (connection.expectInt32() != (BOTTLE_TAG_LIST|BOTTLE_TAG_STRING)) {
            return false;
        }
        int len = connection.expectInt32();
        data.resize(len);
        for (int i=0; i<len; i++) {
            int len2 = connection.expectInt32();
            data[i].resize(len2);
            if (!connection.expectBlock((char*)data[i].c_str(), len2)) {
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
        // *** data ***
        connection.appendInt32(data.size());
        for (size_t i=0; i<data.size(); i++) {
            connection.appendInt32(data[i].length());
            connection.appendExternalBlock((char*)data[i].c_str(), data[i].length());
        }

        return !connection.isError();
    }

    bool writeBottle(yarp::os::ConnectionWriter& connection) const override
    {
        connection.appendInt32(BOTTLE_TAG_LIST);
        connection.appendInt32(1);

        // *** data ***
        connection.appendInt32(BOTTLE_TAG_LIST|BOTTLE_TAG_STRING);
        connection.appendInt32(data.size());
        for (size_t i=0; i<data.size(); i++) {
            connection.appendInt32(data[i].length());
            connection.appendExternalBlock((char*)data[i].c_str(), data[i].length());
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
    typedef yarp::os::idl::BareStyle<yarp::rosmsg::matb_msgs::Strings> rosStyle;
    typedef yarp::os::idl::BottleStyle<yarp::rosmsg::matb_msgs::Strings> bottleStyle;

    // The name for this message, ROS will need this
    static constexpr const char* typeName = "matb_msgs/Strings";

    // The checksum for this message, ROS will need this
    static constexpr const char* typeChecksum = "cce5a364f3a3be12c9722c6dcad2fa94";

    // The source text for this message, ROS will need this
    static constexpr const char* typeText = "\
string[] data\n\
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

#endif // YARP_ROSMSG_matb_msgs_Strings_h
