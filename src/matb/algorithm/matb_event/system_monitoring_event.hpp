#pragma once

#include <iostream>
#include "matb_event_base.hpp"
namespace matb
{
  class SystemMonitoringEvent : public virtual MatbEventBase
  {
    public:
      enum class MonitoringLightType
      {
        NONE, GREEN, RED
      };
      enum class MonitoringScaleNumber
      {
        NONE, ONE, TWO, THREE, FOUR
      };
      enum class MonitoringScaleDirection
      {
        NONE, UP, DOWN
      };
    private:
      MonitoringLightType      monitoring_light_type_;
      MonitoringScaleNumber    monitoring_scale_number_;
      MonitoringScaleDirection monitoring_scale_direction_;
    public:
      SystemMonitoringEvent();
      ~SystemMonitoringEvent();
      virtual MonitoringLightType monitoring_light_type();
      virtual void monitoring_light_type( const MonitoringLightType& _monitoring_light_type );
      virtual MonitoringScaleNumber monitoring_scale_number();
      virtual void monitoring_scale_number( const MonitoringScaleNumber& _monitoring_scale_number );
      virtual MonitoringScaleDirection monitoring_scale_direction();
      virtual void monitoring_scale_direction( const MonitoringScaleDirection& _monitoring_scale_direction );
  };

};
