#include "communications_task.hpp"
namespace matb
{
CommunicationsTask::CommunicationsTask()
{
  com1_timer_.stop();
  com2_timer_.stop();
  nav1_timer_.stop();
  nav2_timer_.stop();

  events_               = MatbEventServer::communication_events();
  line_color            = cv::Scalar( 150, 50, 0 );
  text_color            = cv::Scalar( 150, 50, 0 );
  emphasized_text_color = cv::Scalar( 150, 0, 200 );
  liquid_color          = cv::Scalar( 0, 255, 0 );
  failed_color          = cv::Scalar( 0, 0, 255 );
  bar_color             = cv::Scalar( 255, 150, 150 );
}

CommunicationsTask::~CommunicationsTask()
{
}

void CommunicationsTask::start()
{
  is_started = true;
}

void CommunicationsTask::stop()
{
  is_started = false;
}

void CommunicationsTask::update()
{
  updateState();

  if( is_started )
  {
    updateMatbEvent();
  }

  updateFrequency();
  draw();

  saveLastKeys();
}

void CommunicationsTask::saveLastKeys()
{
  a0_           = a_;
  b0_           = b_;
  x0_           = x_;
  y0_           = y_;
  lb0_          = lb_;
  rb0_          = rb_;
  back0_        = back_;
  start0_       = start_;
  guide0_       = guide_;
  left_stick0_  = left_stick_;
  right_stick0_ = right_stick_;
  left0_        = left_;
  right0_       = right_;
  up0_          = up_;
  down0_        = down_;
}

void CommunicationsTask::updateFrequency()
{
  if( ref_com1_integer_part_ == com1_integer_part_ && ref_com1_decimal_part_ == com1_decimal_part_ )
  {
    com1_timer_.stop();
  }

  if( ref_com2_integer_part_ == com2_integer_part_ && ref_com2_decimal_part_ == com2_decimal_part_ )
  {
    com2_timer_.stop();
  }

  if( ref_nav1_integer_part_ == nav1_integer_part_ && ref_nav1_decimal_part_ == nav1_decimal_part_ )
  {
    nav1_timer_.stop();
  }

  if( ref_nav2_integer_part_ == nav2_integer_part_ && ref_nav2_decimal_part_ == nav2_decimal_part_ )
  {
    nav2_timer_.stop();
  }

  switch( current_state )
  {
    case State::NAV1:
      break;

    case State::NAV1_INTEGER:
      if( up_ && !up0_ )
      {
        nav1_integer_part_ = nav1_integer_part_ + 10;
      }

      if( down_ && !down0_ )
      {
        nav1_integer_part_ = nav1_integer_part_ - 10;
      }

      break;

    case State::NAV1_DECIMAL:
      if( up_ && !up0_ )
      {
        nav1_decimal_part_ = nav1_decimal_part_ + 100;
      }

      if( down_ && !down0_ )
      {
        nav1_decimal_part_ = nav1_decimal_part_ - 100;
      }

      break;

    case State::NAV2:
      break;

    case State::NAV2_INTEGER:
      if( up_ && !up0_ )
      {
        nav2_integer_part_ = nav2_integer_part_ + 10;
      }

      if( down_ && !down0_ )
      {
        nav2_integer_part_ = nav2_integer_part_ - 10;
      }

      break;

    case State::NAV2_DECIMAL:
      if( up_ && !up0_ )
      {
        nav2_decimal_part_ = nav2_decimal_part_ + 100;
      }

      if( down_ && !down0_ )
      {
        nav2_decimal_part_ = nav2_decimal_part_ - 100;
      }

      break;

    case State::COM1:
      break;

    case State::COM1_INTEGER:
      if( up_ && !up0_ )
      {
        com1_integer_part_  = com1_integer_part_ + 10;
      }

      if( down_ && !down0_ )
      {
        com1_integer_part_  = com1_integer_part_ - 10;
      }

      break;

    case State::COM1_DECIMAL:
      if( up_ && !up0_ )
      {
        com1_decimal_part_ = com1_decimal_part_ + 100;
      }

      if( down_ && !down0_ )
      {
        com1_decimal_part_ = com1_decimal_part_ - 100;
      }

      break;

    case State::COM2:
      break;

    case State::COM2_INTEGER:
      if( up_ && !up0_ )
      {
        com2_integer_part_  = com2_integer_part_ + 10;
      }

      if( down_ && !down0_ )
      {
        com2_integer_part_ = com2_integer_part_ - 10;
      }

      break;

    case State::COM2_DECIMAL:
      if( up_ && !up0_ )
      {
        com2_decimal_part_ = com2_decimal_part_ + 100;
      }

      if( down_ && !down0_ )
      {
        com2_decimal_part_ = com2_decimal_part_ - 100;
      }

      break;

    default:
      break;
  }

  if( nav1_integer_part_ < freq_min_ )
  {
    nav1_integer_part_ = freq_min_;
  }
  else if( nav1_integer_part_ > freq_max_ )
  {
    nav1_integer_part_ = freq_max_;
  }

  if( nav1_decimal_part_ < 0 )
  {
    nav1_decimal_part_ = 0;
  }
  else if( nav1_decimal_part_ > 900 )
  {
    nav1_decimal_part_ = 900;
  }

  if( nav2_integer_part_ < freq_min_ )
  {
    nav2_integer_part_ = freq_min_;
  }
  else if( nav2_integer_part_ > freq_max_ )
  {
    nav2_integer_part_ = freq_max_;
  }

  if( nav2_decimal_part_ < 0 )
  {
    nav2_decimal_part_ = 0;
  }
  else if( nav2_decimal_part_ > 900 )
  {
    nav2_decimal_part_ = 900;
  }

  if( com1_integer_part_ < freq_min_ )
  {
    com1_integer_part_ = freq_min_;
  }
  else if( com1_integer_part_ > freq_max_ )
  {
    com1_integer_part_ = freq_max_;
  }

  if( com1_decimal_part_ < 0 )
  {
    com1_decimal_part_ = 0;
  }
  else if( com1_decimal_part_ > 900 )
  {
    com1_decimal_part_ = 900;
  }

  if( com2_integer_part_ < freq_min_ )
  {
    com2_integer_part_ = freq_min_;
  }
  else if( com2_integer_part_ > freq_max_ )
  {
    com2_integer_part_ = freq_max_;
  }

  if( com2_decimal_part_ < 0 )
  {
    com2_decimal_part_ = 0;
  }
  else if( com2_decimal_part_ > 900 )
  {
    com2_decimal_part_ = 900;
  }
}

void CommunicationsTask::updateState()
{
  switch( current_state )
  {
    case State::NAV1:
      if( right_ && !right0_ )
      {
        current_state = State::NAV1_INTEGER;
      }
      else if( down_ && !down0_ )
      {
        current_state = State::NAV2;
      }
      else
      {
      }

      break;

    case State::NAV1_INTEGER:
      if( left_ && !left0_ )
      {
        current_state = State::NAV1;
      }
      else if( right_ && !right0_ )
      {
//         current_state = State::NAV1_DECIMAL;
      }
      else
      {
      }

      break;

    case State::NAV1_DECIMAL:
      if( left_ && !left0_ )
      {
        current_state = State::NAV1_INTEGER;
      }
      else
      {
      }

      break;

    case State::NAV2:
      if( right_ && !right0_ )
      {
        current_state = State::NAV2_INTEGER;
      }
      else if( down_ && !down0_ )
      {
        current_state = State::COM1;
      }
      else if( up_ && !up0_ )
      {
        current_state = State::NAV1;
      }
      else
      {
      }

      break;

    case State::NAV2_INTEGER:
      if( left_ && !left0_ )
      {
        current_state = State::NAV2;
      }
      else if( right_ && !right0_ )
      {
//         current_state = State::NAV2_DECIMAL;
      }
      else
      {
      }

      break;

    case State::NAV2_DECIMAL:
      if( left_ && !left0_ )
      {
        current_state = State::NAV2_INTEGER;
      }
      else
      {
      }

      break;

    case State::COM1:
      if( right_ && !right0_ )
      {
        current_state = State::COM1_INTEGER;
      }
      else if( down_ && !down0_ )
      {
        current_state = State::COM2;
      }
      else if( up_ && !up0_ )
      {
        current_state = State::NAV2;
      }
      else
      {
      }

      break;

    case State::COM1_INTEGER:
      if( left_ && !left0_ )
      {
        current_state = State::COM1;
      }
      else if( right_ && !right0_ )
      {
//         current_state = State::COM1_DECIMAL;
      }
      else
      {
      }

      break;

    case State::COM1_DECIMAL:
      if( left_ && !left0_ )
      {
        current_state = State::COM1_INTEGER;
      }
      else
      {
      }

      break;

    case State::COM2:
      if( right_ && !right0_ )
      {
        current_state = State::COM2_INTEGER;
      }
      else if( up_ && !up0_ )
      {
        current_state = State::COM1;
      }
      else
      {
      }

      break;

    case State::COM2_INTEGER:
      if( left_ && !left0_ )
      {
        current_state = State::COM2;
      }
      else if( right_ && !right0_ )
      {
//         current_state = State::COM2_DECIMAL;
      }
      else
      {
      }

      break;

    case State::COM2_DECIMAL:
      if( left_ && !left0_ )
      {
        current_state = State::COM2_INTEGER;
      }
      else
      {
      }

      break;

    default:
      break;
  }
}

void CommunicationsTask::draw()
{
  cv_image = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );
  std::string nav1_decimal_string = "." + std::to_string( ( nav1_decimal_part_ / 100 ) ) + std::to_string( ( nav1_decimal_part_ / 10 ) % 10 ) + std::to_string( nav1_decimal_part_ % 10 );
  std::string nav1_integer_string = std::to_string( ( nav1_integer_part_ / 100 ) ) + std::to_string( ( nav1_integer_part_ / 10 ) % 10 ) + std::to_string( nav1_integer_part_ % 10 );
  std::string nav2_decimal_string = "." + std::to_string( ( nav2_decimal_part_ / 100 ) ) + std::to_string( ( nav2_decimal_part_ / 10 ) % 10 ) + std::to_string( nav2_decimal_part_ % 10 );
  std::string nav2_integer_string = std::to_string( ( nav2_integer_part_ / 100 ) ) + std::to_string( ( nav2_integer_part_ / 10 ) % 10 ) + std::to_string( nav2_integer_part_ % 10 );
  std::string com1_decimal_string = "." + std::to_string( ( com1_decimal_part_ / 100 ) ) + std::to_string( ( com1_decimal_part_ / 10 ) % 10 ) + std::to_string( com1_decimal_part_ % 10 );
  std::string com1_integer_string = std::to_string( ( com1_integer_part_ / 100 ) ) + std::to_string( ( com1_integer_part_ / 10 ) % 10 ) + std::to_string( com1_integer_part_ % 10 );
  std::string com2_decimal_string = "." + std::to_string( ( com2_decimal_part_ / 100 ) ) + std::to_string( ( com2_decimal_part_ / 10 ) % 10 ) + std::to_string( com2_decimal_part_ % 10 );
  std::string com2_integer_string = std::to_string( ( com2_integer_part_ / 100 ) ) + std::to_string( ( com2_integer_part_ / 10 ) % 10 ) + std::to_string( com2_integer_part_ % 10 );

  switch( current_state )
  {
    case State::NAV1:
      nav1_text_color         = emphasized_text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::NAV1_INTEGER:
      nav1_text_color         = text_color;
      nav1_integer_text_color = emphasized_text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::NAV1_DECIMAL:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = emphasized_text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::NAV2:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = emphasized_text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::NAV2_INTEGER:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = emphasized_text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::NAV2_DECIMAL:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = emphasized_text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM1:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = emphasized_text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM1_INTEGER:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = emphasized_text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM1_DECIMAL:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = emphasized_text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM2:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = emphasized_text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM2_INTEGER:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = emphasized_text_color;
      com2_decimal_text_color = text_color;
      break;

    case State::COM2_DECIMAL:
      nav1_text_color         = text_color;
      nav1_integer_text_color = text_color;
      nav1_decimal_text_color = text_color;
      nav2_text_color         = text_color;
      nav2_integer_text_color = text_color;
      nav2_decimal_text_color = text_color;
      com1_text_color         = text_color;
      com1_integer_text_color = text_color;
      com1_decimal_text_color = text_color;
      com2_text_color         = text_color;
      com2_integer_text_color = text_color;
      com2_decimal_text_color = emphasized_text_color;
      break;

    default:
      break;
  }

  putText( cv_image, "Call Sign:    NASA504", cv::Point( pixel_size * 4.5 / 20, pixel_size * 5 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, "NAV 1", cv::Point( pixel_size * 4.5 / 20, pixel_size * 8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav1_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, nav1_integer_string, cv::Point( pixel_size * 12 / 20, pixel_size * 8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav1_integer_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, " Hz", cv::Point( pixel_size * 13.5 / 20, pixel_size * 8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
//  putText( cv_image, nav1_decimal_string, cv::Point( pixel_size * 11.7 / 20, pixel_size * 8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav1_decimal_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, "NAV 2", cv::Point( pixel_size * 4.5 / 20, pixel_size * 10 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav2_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, nav2_integer_string, cv::Point( pixel_size * 12 / 20, pixel_size * 10 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav2_integer_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, " Hz", cv::Point( pixel_size * 13.5 / 20, pixel_size * 10 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
//  putText( cv_image, nav2_decimal_string, cv::Point( pixel_size * 11.7 / 20, pixel_size * 10 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, nav2_decimal_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, "COM 1", cv::Point( pixel_size * 4.5 / 20, pixel_size * 12 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com1_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, com1_integer_string, cv::Point( pixel_size * 12 / 20, pixel_size * 12 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com1_integer_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, " Hz", cv::Point( pixel_size * 13.5 / 20, pixel_size * 12 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
//  putText( cv_image, com1_decimal_string, cv::Point( pixel_size * 11.7 / 20, pixel_size * 12 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com1_decimal_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, "COM 2", cv::Point( pixel_size * 4.5 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com2_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, com2_integer_string, cv::Point( pixel_size * 12 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com2_integer_text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, " Hz", cv::Point( pixel_size * 13.5 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
// putText( cv_image, com2_decimal_string, cv::Point( pixel_size * 11.7 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, com2_decimal_text_color, text_thickness, cv::LINE_AA );
}

void CommunicationsTask::updateMatbEvent()
{
  for( auto it = events_.begin(); it != events_.end(); ++it )
  {
    if( !it->get()->checkDone() )
    {
      auto elapsed_time = MatbEventServer::elapsed_time();
      auto event_time   = std::chrono::duration_cast< std::chrono::nanoseconds >( it->get()->start_time() ).count();

      if( ( elapsed_time - event_time ) >= 0 )
      {
        std::string hz       = it->get()->freq();
        std::string hz_space = "";

        for( auto a = 0; a < hz.size(); ++a )
        {
          hz_space.append( hz.substr( 0, a ) );
          hz_space.append( " " );
        }

        if( CommunicationEvent::Ship::OTHER == it->get()->ship() )
        {
//           instruction_comment_ = " Delta 1 7 0 1, Delta 1 7 0 1, ";
//           std::string freq = it->get()->freq();
//           freq.find_first_of( "." );
//           freq.insert( 6, " " );
//           freq.insert( 5, " " );
//           freq.insert( 4, " " );
//           freq.insert( 3, " " );
//           freq.insert( 2, " " );
//           freq.insert( 1, " " );
//           freq.replace( freq.find_first_of( "." ), 1, "point, " );

//           if( CommunicationEvent::Radio::COM1 == it->get()->radio() )
//           {
//             instruction_comment_.append( " tune your Com1 radio, to frequecncy " );
//             instruction_comment_.append( freq );
//           }
//           else if( CommunicationEvent::Radio::COM2 == it->get()->radio() )
//           {
//             instruction_comment_.append( " tune your Com2 radio, to frequecncy " );
//             instruction_comment_.append( freq );
//           }
//           else if( CommunicationEvent::Radio::NAV1 == it->get()->radio() )
//           {
//             instruction_comment_.append( " tune your Nav1 radio, to frequecncy " );
//             instruction_comment_.append( freq );
//           }
//           else if( CommunicationEvent::Radio::NAV2 == it->get()->radio() )
//           {
//             instruction_comment_.append( " tune your Nav2 radio, to frequecncy " );
//             instruction_comment_.append( freq );
//           }
//           else
//           {
//           }

        }
        else if( CommunicationEvent::Ship::OWN == it->get()->ship() )
        {
          instruction_comment_ = "";
          std::string freq = it->get()->freq();
          std::string freq_for_speech = it->get()->freq();
          freq_for_speech.replace( 3, 4, "" );
//           freq_for_speech.insert( 6, " " );
//           freq_for_speech.insert( 5, " " );
//           freq_for_speech.insert( 4, " " );
//           freq_for_speech.insert( 3, " " );
//           freq_for_speech.insert( 2, " " );
//           freq_for_speech.insert( 1, " " );
//           freq_for_speech.replace( freq_for_speech.find_first_of( "." ), 1, "point, " );

          if( CommunicationEvent::Radio::COM1 == it->get()->radio() )
          {
//             instruction_comment_.append( " tune your Com1 radio, to frequecncy " );
            instruction_comment_.append( "Sintonizza la tua COM1 alla" );
            instruction_comment_.append( freq_for_speech );
            instruction_comment_.append( " Hz." );
            com1_timer_.start();
            ref_com1_integer_part_ = std::stoi( freq.substr( 0, 3 ) );
            ref_com1_decimal_part_ = std::stoi( freq.substr( 4, 3 ) );
          }
          else if( CommunicationEvent::Radio::COM2 == it->get()->radio() )
          {
//             instruction_comment_.append( " tune your Com2 radio, to frequecncy " );
            instruction_comment_.append( "Sintonizza la tua COM2 alla" );
            instruction_comment_.append( freq_for_speech );
            instruction_comment_.append( " Hz." );
            com2_timer_.start();
            ref_com2_integer_part_ = std::stoi( freq.substr( 0, 3 ) );
            ref_com2_decimal_part_ = std::stoi( freq.substr( 4, 3 ) );
          }
          else if( CommunicationEvent::Radio::NAV1 == it->get()->radio() )
          {
//            instruction_comment_.append( " tune your Nav1 radio, to frequecncy " );
            instruction_comment_.append( "Sintonizza la tua NAV1 alla" );
            instruction_comment_.append( freq_for_speech );
            instruction_comment_.append( " Hz." );
            nav1_timer_.start();
            ref_nav1_integer_part_ = std::stoi( freq.substr( 0, 3 ) );
            ref_nav1_decimal_part_ = std::stoi( freq.substr( 4, 3 ) );

          }
          else if( CommunicationEvent::Radio::NAV2 == it->get()->radio() )
          {
//            instruction_comment_.append( " tune your Nav2 radio, to frequecncy " );
            instruction_comment_.append( "Sintonizza la tua NAV2 alla" );
            instruction_comment_.append( freq_for_speech );
            instruction_comment_.append( " Hz." );
            nav2_timer_.start();
            ref_nav2_integer_part_ = std::stoi( freq.substr( 0, 3 ) );
            ref_nav2_decimal_part_ = std::stoi( freq.substr( 4, 3 ) );

          }
          else
          {
          }
        }
        else
        {
        }

        need_instruction_ = true;
        it->get()->done();
      }
      else
      {
      }
    }
  }
}


};

