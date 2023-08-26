#include "matb_event.hpp"
namespace matb
{
  MatbEventBase::MatbEventBase()
  {
  }

  MatbEventBase::~MatbEventBase()
  {
  }

  void MatbEventBase::start_time( const std::chrono::seconds& _start_time )
  {
    start_time_ = _start_time;
  }

  std::chrono::seconds MatbEventBase::start_time()
  {
    return start_time_;
  }

  void MatbEventBase::event( const MatbEventBase::Event& _event )
  {
    event_ = _event;
  }

  MatbEventBase::Event MatbEventBase::event()
  {
    return event_;
  }

  void MatbEventBase::done()
  {
    done_ = true;
  }

  bool MatbEventBase::checkDone()
  {
    return done_;
  }
};
