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
  class JoystickButtonSubscriber : public yarp::os::TypedReaderCallback< yarp::os::Bottle >, public yarp::os::PortReader
  {
    public:
    bool b();
    bool a();
    bool y();
    bool x();
    bool lb();
    bool rb();
    bool back();
    bool start();
    bool guide();
    bool left_stick();
    bool right_stick();
    bool left();
    bool right();
    bool up();
    bool down();
    protected:
    virtual void onRead( yarp::os::Bottle& _bottle );
    virtual bool read( yarp::os::ConnectionReader& _connection );
    private:
    bool b_           = false;
    bool a_           = false;
    bool y_           = false;
    bool x_           = false;
    bool lb_          = false;
    bool rb_          = false;
    bool back_        = false;
    bool start_       = false;
    bool guide_       = false;
    bool left_stick_  = false;
    bool right_stick_ = false;
    bool left_        = false;
    bool right_       = false;
    bool up_          = false;
    bool down_        = false;
  };
};
