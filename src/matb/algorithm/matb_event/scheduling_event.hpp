#pragma once

#include <iostream>
#include "matb_event_base.hpp"
namespace matb
{
  class SchedulingEvent : public virtual MatbEventBase
  {
    public:
      enum class Task
      {
        NONE, COMM, RESMAN, RESSYS, SYSMON, TRACK
      };
      enum class Action
      {
        NONE, MANUAL, AUTO, START, STOP
      };
      enum class Update
      {
        NONE, LOW, MEDIUM, HIGH
      };
      enum class Response
      {
        NONE, LOW, MEDIUM, HIGH
      };
    private:
      Task     task_;
      Action   action_;
      Update   update_;
      Response response_;
    public:
      SchedulingEvent();
      ~SchedulingEvent();
      virtual Task task();
      virtual void task( const Task& _task );
      virtual Action action();
      virtual void action( const Action& _action );
      virtual Update update();
      virtual void update( const Update& _update );
      virtual Response response();
      virtual void response( const Response& _response );
  };
};
