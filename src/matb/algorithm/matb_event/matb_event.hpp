#pragma once

#include <iostream>
#include <istream>
#include "communication_event.hpp"
#include "resource_management_event.hpp"
#include "scheduling_event.hpp"
#include "system_event.hpp"
#include "system_monitoring_event.hpp"
namespace matb
{
  class MatbEvent : public virtual CommunicationEvent, public virtual ResourceManagementEvent, public virtual SchedulingEvent, public virtual SystemMonitoringEvent, public virtual SystemEvent
  {
  };
};
