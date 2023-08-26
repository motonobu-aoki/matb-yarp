#include "communication_event.hpp"
namespace matb
{
  CommunicationEvent::CommunicationEvent()
  {
    event_ = Event::COMM;
  }

  CommunicationEvent::~CommunicationEvent()
  {
  }

  CommunicationEvent::Radio CommunicationEvent::radio()
  {
    return radio_;
  }

  void CommunicationEvent::radio( const CommunicationEvent::Radio& _radio )
  {
    radio_ = _radio;
  }

  CommunicationEvent::Ship CommunicationEvent::ship()
  {
    return ship_;
  }

  void CommunicationEvent::ship( const CommunicationEvent::Ship& _ship )
  {
    ship_ = _ship;
  }

  std::string CommunicationEvent::freq()
  {
    return freq_;
  }

  void CommunicationEvent::freq( const std::string& _freq )
  {
    freq_ = _freq;
  }
};
