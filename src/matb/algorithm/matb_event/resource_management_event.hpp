#pragma once

#include <iostream>
#include "matb_event_base.hpp"
namespace matb
{
  class ResourceManagementEvent : public virtual MatbEventBase
  {
    public:
      enum class Fail
      {
        NONE, P1, P2, P3, P4, P5, P6, P7, P8
      };
      enum class Fix
      {
        NONE, P1, P2, P3, P4, P5, P6, P7, P8
      };
    private:
      Fail fail_ = Fail::NONE;
      Fix  fix_  = Fix::NONE;
    public:
      ResourceManagementEvent();
      ~ResourceManagementEvent();
      virtual Fail fail();
      virtual void fail( const Fail& _fail );
      virtual Fix fix();
      virtual void fix( const Fix& _fix );
  };
};

