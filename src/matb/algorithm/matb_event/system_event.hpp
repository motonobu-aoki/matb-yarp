#pragma once

#include <iostream>
#include "matb_event_base.hpp"
namespace matb
{
  class SystemEvent : public virtual MatbEventBase
  {
    public:
      enum class Control
      {
        NONE, START, END
      };
      enum class WRS
      {
        NONE, START, END
      };
    private:
      Control control_;
      WRS     wrs_;
    public:
      SystemEvent();
      ~SystemEvent();
      virtual Control control();
      virtual void control( const Control& _control );
      virtual WRS wrs();
      virtual void wrs( const WRS& _wrs );
  };

};
