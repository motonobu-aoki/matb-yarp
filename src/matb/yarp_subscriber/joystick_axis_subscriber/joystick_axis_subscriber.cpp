#include "joystick_axis_subscriber.hpp"

namespace matb
{
    void JoystickAxisSubscriber::onRead(yarp::os::Bottle& _bottle)
    {
        if(_bottle.size() > 5)
        {
            lx_ = _bottle.get(0).asFloat64();
            ly_ = _bottle.get(1).asFloat64();
            left_ = _bottle.get(2).asFloat64();
            rx_ = _bottle.get(3).asFloat64();
            ry_ = _bottle.get(4).asFloat64();
            right_ = _bottle.get(5).asFloat64();
        }
    }

    bool JoystickAxisSubscriber::read(yarp::os::ConnectionReader& _connection)
    {
        return true;
    }

    double JoystickAxisSubscriber::lx()
    {
        return lx_;
    }

    double JoystickAxisSubscriber::ly()
    {
        return ly_;
    }

    double JoystickAxisSubscriber::rx()
    {
        return rx_;
    }

    double JoystickAxisSubscriber::ry()
    {
        return ry_;
    }

    double JoystickAxisSubscriber::left()
    {
        return left_;
    }

    double JoystickAxisSubscriber::right()
    {
        return right_;
    }
};
