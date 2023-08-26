#include "resource_management_event.hpp"
namespace matb
{
  ResourceManagementEvent::ResourceManagementEvent()
  {
    event_ = Event::RESMAN;
  }

  ResourceManagementEvent::~ResourceManagementEvent()
  {
  }

  ResourceManagementEvent::Fail ResourceManagementEvent::fail()
  {
    return fail_;
  }

  void ResourceManagementEvent::fail( const ResourceManagementEvent::Fail& _fail )
  {
    fail_ = _fail;
  }

  ResourceManagementEvent::Fix ResourceManagementEvent::fix()
  {
    return fix_;
  }

  void ResourceManagementEvent::fix( const ResourceManagementEvent::Fix& _fix )
  {
    fix_ = _fix;
  }
};
