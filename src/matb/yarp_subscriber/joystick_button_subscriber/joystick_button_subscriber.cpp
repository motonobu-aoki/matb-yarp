#include "joystick_button_subscriber.hpp"

namespace matb
{
    void JoystickButtonSubscriber::onRead(yarp::os::Bottle& _bottle)
    {
        if(_bottle.size() > 5)
        {
            a_ = _bottle.get(0).asFloat64();
            b_ = _bottle.get(1).asFloat64();
            x_ = _bottle.get(2).asFloat64();
            y_ = _bottle.get(3).asFloat64();
            lb_ = _bottle.get(4).asFloat64();
            rb_ = _bottle.get(5).asFloat64();
            back_ = _bottle.get(6).asFloat64();
            start_ = _bottle.get(7).asFloat64();
            guide_ = _bottle.get(8).asFloat64();
            left_stick_ = _bottle.get(9).asFloat64();
            right_stick_ = _bottle.get(10).asFloat64();
            left_ = _bottle.get(11).asFloat64();
            right_ = _bottle.get(12).asFloat64();
            up_ = _bottle.get(13).asFloat64();
            down_ = _bottle.get(14).asFloat64();
        }
    }

    bool JoystickButtonSubscriber::read(yarp::os::ConnectionReader& _connection)
    {
        return true;
    }

    bool JoystickButtonSubscriber::a()
    {
        return a_;
    }

    bool JoystickButtonSubscriber::b()
    {
        return b_;
    }

    bool JoystickButtonSubscriber::x()
    {
        return x_;
    }

    bool JoystickButtonSubscriber::y()
    {
        return y_;
    }

    bool JoystickButtonSubscriber::lb()
    {
        return lb_;
    }

    bool JoystickButtonSubscriber::rb()
    {
        return rb_;
    }

    bool JoystickButtonSubscriber::back()
    {
        return back_;
    }

    bool JoystickButtonSubscriber::start()
    {
        return start_;
    }

    bool JoystickButtonSubscriber::guide()
    {
        return guide_;
    }

    bool JoystickButtonSubscriber::left_stick()
    {
        return left_stick_;
    }

    bool JoystickButtonSubscriber::right_stick()
    {
        return right_stick_;
    }

    bool JoystickButtonSubscriber::left()
    {
        return left_;
    }

    bool JoystickButtonSubscriber::right()
    {
        return right_;
    }

    bool JoystickButtonSubscriber::up()
    {
        return up_;
    }

    bool JoystickButtonSubscriber::down()
    {
        return down_;
    }
};
