#pragma once

#include <iostream>
#include <chrono>
#include <mutex>
#include <utility>
#include <cstdio>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>

namespace matb
{
    template<class BottleType> class YarpSubscriber : public yarp::os::TypedReaderCallback<BottleType>, public yarp::os::PortReader
    {
    protected:
        std::mutex mutex_;
        BottleType bottle_;

        std::chrono::system_clock::time_point time_point_;
    public:
        BottleType bottle();
        std::chrono::system_clock::time_point time();
        std::pair <BottleType, std::chrono::system_clock::time_point> bottleWithTime();

    protected:
        virtual void onRead(BottleType& _bottle) override;
        virtual bool read(yarp::os::ConnectionReader& _connection) override;

    };
};
namespace matb
{
    template<class BottleType> void YarpSubscriber<BottleType>::onRead(BottleType& _bottle)
    {
        std::lock_guard <std::mutex> lock(mutex_);
        bottle_ = _bottle;
        time_point_ = std::chrono::system_clock::now();
    }

    template<class BottleType> bool YarpSubscriber<BottleType>::read(yarp::os::ConnectionReader& _connection)
    {
        std::lock_guard <std::mutex> lock(mutex_);
        return true;
    }

    template<class BottleType> BottleType YarpSubscriber<BottleType>::bottle()
    {
        std::lock_guard <std::mutex> lock(mutex_);
        return bottle_;
    }

    template<class BottleType> std::chrono::system_clock::time_point YarpSubscriber<BottleType>::time()
    {
        std::lock_guard <std::mutex> lock(mutex_);
        return time_point_;
    }

    template<class BottleType> std::pair <BottleType, std::chrono::system_clock::time_point> YarpSubscriber<BottleType>::bottleWithTime()
    {
        std::lock_guard <std::mutex> lock(mutex_);
        return std::make_pair(bottle_, time_point_);
    }


};



