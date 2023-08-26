#include "system_monitoring_event.hpp"
namespace matb
{
  SystemMonitoringEvent::SystemMonitoringEvent()
  {
    event_ = Event::SYSMON;
  }

  SystemMonitoringEvent::~SystemMonitoringEvent()
  {
  }

  SystemMonitoringEvent::MonitoringLightType SystemMonitoringEvent::monitoring_light_type()
  {
    return monitoring_light_type_;
  }

  void SystemMonitoringEvent::monitoring_light_type( const SystemMonitoringEvent::MonitoringLightType& _monitoring_light_type )
  {
    monitoring_light_type_ = _monitoring_light_type;
  }

  SystemMonitoringEvent::MonitoringScaleDirection SystemMonitoringEvent::monitoring_scale_direction()
  {
    return monitoring_scale_direction_;
  }

  void SystemMonitoringEvent::monitoring_scale_direction( const SystemMonitoringEvent::MonitoringScaleDirection& _monitoring_scale_direction )
  {
    monitoring_scale_direction_ = _monitoring_scale_direction;
  }

  SystemMonitoringEvent::MonitoringScaleNumber SystemMonitoringEvent::monitoring_scale_number()
  {
    return monitoring_scale_number_;
  }

  void SystemMonitoringEvent::monitoring_scale_number( const SystemMonitoringEvent::MonitoringScaleNumber& _monitoring_scale_number )
  {
    monitoring_scale_number_ = _monitoring_scale_number;
  }

};
