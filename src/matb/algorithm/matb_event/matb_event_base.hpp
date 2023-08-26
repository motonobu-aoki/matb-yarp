#pragma once

#include <iostream>
#include <istream>
#include <chrono>
namespace matb
{
  class MatbEventBase
  {
    public:
      enum class Event
      {
        NONE, MATB, SYSMON, SCHED, COMM, RESMAN,
      };
      MatbEventBase();
      ~MatbEventBase();
    protected:
      std::chrono::seconds start_time_;

      Event event_ = Event::NONE;
      bool  done_  = false;
    public:
      virtual std::chrono::seconds start_time();
      virtual void start_time( const std::chrono::seconds& _start_time );
      virtual Event event();
      virtual void event( const Event& _event );
      virtual void done();
      virtual bool checkDone();
  };
};
