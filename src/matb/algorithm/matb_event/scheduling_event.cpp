#include "scheduling_event.hpp"
namespace matb
{
  SchedulingEvent::SchedulingEvent()
  {
    event_ = Event::SCHED;
  }

  SchedulingEvent::~SchedulingEvent()
  {
  }

  SchedulingEvent::Action SchedulingEvent::action()
  {
    return action_;
  }

  void SchedulingEvent::action( const SchedulingEvent::Action& _action )
  {
    action_ = _action;
  }

  SchedulingEvent::Response SchedulingEvent::response()
  {
    return response_;
  }

  void SchedulingEvent::response( const SchedulingEvent::Response& _response )
  {
    response_ = _response;
  }

  SchedulingEvent::Task SchedulingEvent::task()
  {
    return task_;
  }

  void SchedulingEvent::task( const SchedulingEvent::Task& _task )
  {
    task_ = _task;
  }

  SchedulingEvent::Update SchedulingEvent::update()
  {
    return update_;
  }

  void SchedulingEvent::update( const SchedulingEvent::Update& _update )
  {
    update_ = _update;
  }
};
