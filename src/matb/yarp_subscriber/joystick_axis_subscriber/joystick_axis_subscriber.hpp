#pragma once

#include <iostream>
#include <cstdio>
#include <thread>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/PortReader.h>
#include <yarp/os/TypedReaderCallback.h>

namespace matb
{
    class JoystickAxisSubscriber : public yarp::os::TypedReaderCallback<yarp::os::Bottle>, public yarp::os::PortReader
    {
    public:
        double left();
        double lx();
        double ly();
        double right();
        double rx();
        double ry();
    protected:
        virtual void onRead(yarp::os::Bottle& _bottle);
        virtual bool read(yarp::os::ConnectionReader& _connection);
    private:
        double left_ = 0.0;
        double lx_ = 0.0;
        double ly_ = 0.0;
        double right_ = 0.0;
        double rx_ = 0.0;
        double ry_ = 0.0;
    };
};
