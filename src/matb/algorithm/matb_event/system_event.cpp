#include "system_event.hpp"
namespace matb
{
  SystemEvent::SystemEvent()
  {
    event_ = Event::SYSMON;
  }

  SystemEvent::~SystemEvent()
  {
  }

  SystemEvent::Control SystemEvent::control()
  {
    return control_;
  }

  void SystemEvent::control( const SystemEvent::Control& _control )
  {
    control_ = _control;
  }

  SystemEvent::WRS SystemEvent::wrs()
  {
    return wrs_;
  }

  void SystemEvent::wrs( const SystemEvent::WRS& _wrs )
  {
    wrs_ = _wrs;
  }
};
