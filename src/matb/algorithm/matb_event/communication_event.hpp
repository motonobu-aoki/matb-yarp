#pragma once

#include <iostream>
#include "matb_event_base.hpp"
namespace matb
{
  class CommunicationEvent : public virtual MatbEventBase
  {
    public:
      enum class Ship
      {
        NONE, OWN, OTHER
      };
      enum class Radio
      {
        NONE, NAV1, NAV2, COM1, COM2
      };
      CommunicationEvent();
      ~CommunicationEvent();
    private:
      Ship        ship_;
      Radio       radio_;
      std::string freq_ = "";
    public:
      virtual Ship ship();
      virtual void ship( const Ship& _ship );
      virtual Radio radio();
      virtual void radio( const Radio& _radio );
      virtual std::string freq();
      virtual void freq( const std::string& _freq );
  };

};

