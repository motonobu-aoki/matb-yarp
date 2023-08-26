#include "scheduling_display.hpp"
namespace matb
{
SchedulingDisplay::SchedulingDisplay()
{
  system_events_     = MatbEventServer::system_events();
  scheduling_events_ = MatbEventServer::scheduling_events();
  takeInEachTaskStartAndEndTime();
  line_color   = cv::Scalar( 150, 50, 0 );
  text_color   = cv::Scalar( 150, 50, 0 );
  gage_color   = cv::Scalar( 100, 200, 100 );
  failed_color = cv::Scalar( 0, 0, 255 );
  bar_color    = cv::Scalar( 255, 150, 150 );
}

SchedulingDisplay::~SchedulingDisplay()
{
}

void SchedulingDisplay::update()
{
  draw();
}

void SchedulingDisplay::start()
{
  is_started = true;
}

void SchedulingDisplay::stop()
{
  is_started = false;
}

void SchedulingDisplay::draw()
{

  cv_image = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );
  drawSchedulingGraph();

  if( is_started )
  {
    drawElapsedTime();
  }
}

void SchedulingDisplay::drawSchedulingGraph()
{

  /* text */

  putText( cv_image, std::string( "COMMUNICATION" ), cv::Point( pixel_size * 3 / 20, pixel_size * 1.5 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 1000, text_color, text_thickness, cv::LINE_AA );
  putText( cv_image, std::string( "TRACKING" ), cv::Point( pixel_size * 13 / 20, pixel_size * 1.5 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 1000, text_color, text_thickness / 2, cv::LINE_AA );
  putText( cv_image, std::string( "[min]" ), cv::Point( pixel_size * 9 / 20, pixel_size * 1.5 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 1000, text_color, text_thickness / 2, cv::LINE_AA );

  /* bar */

  auto elapsed_time = MatbEventServer::elapsed_time() / 1000000000;

  if( 0 <= double( control_end_time.count() - elapsed_time ) && double( control_end_time.count() - elapsed_time ) < max_second_ )
  {
    /* communication bar */
    cv::line( cv_image, cv::Point( pixel_size * 6 / 20, pixel_size * 2.0 / 20 ), cv::Point( pixel_size * 6 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * 16.0 / 20 ) ), line_color, line_thickness * 2, cv::LINE_8 );

    /* communication end */
    cv::line( cv_image, cv::Point( pixel_size * 5.75 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point(
                pixel_size * 6.25 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), line_color, line_thickness * 2, cv::LINE_8 );
  }
  else if( double( max_second_ ) <= double( control_end_time.count() - elapsed_time ) )
  {
    /* communication bar */
    cv::line( cv_image, cv::Point( pixel_size * 6 / 20, pixel_size * 2.0 / 20 ), cv::Point( pixel_size * 6 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20 ) ), line_color, line_thickness * 2, cv::LINE_8 );

    /* communication end */
    cv::line( cv_image, cv::Point( pixel_size * 5.75 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20.0 ) ), cv::Point( pixel_size * 6.25 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20.0 ) ), line_color, line_thickness * 2, cv::LINE_8 );
  }


  /* communication gage */
  for( auto it = communication_task_durations.begin(); it != communication_task_durations.end(); ++it )
  {
    if( ( it->first.count() - elapsed_time ) >= 0 && ( it->second.count() - elapsed_time ) >= 0 )
    {
      if( it->second.count() - elapsed_time < max_second_ )
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 5.5 / 20, pixel_size * ( 2.0 / 20 + double( it->first.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point(
                         pixel_size * 6.5 / 20, pixel_size * ( 2.0 / 20 + double( it->second.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
      else
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 5.5 / 20, pixel_size * ( 2.0 / 20 + double( it->first.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point( pixel_size * 6.5 / 20, pixel_size * ( 2.0 / 20 + double( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }

    }
    else if( ( it->first.count() - elapsed_time ) < 0 && ( it->second.count() - elapsed_time ) > 0 )
    {
      if( it->second.count() - elapsed_time < max_second_ )
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 5.5 / 20, pixel_size * ( 2.0 / 20 ) ), cv::Point( pixel_size * 6.5 / 20, pixel_size * ( 2.0 / 20 + double( it->second.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
      else
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 5.5 / 20, pixel_size * ( 2.0 / 20 ) ), cv::Point( pixel_size * 6.5 / 20, pixel_size * ( 2.0 / 20 + double( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );

      }
    }
    else if( ( it->first.count() - elapsed_time ) < 0 && ( it->second.count() - elapsed_time ) < 0 )
    {
    }
    else if( ( it->first.count() - elapsed_time ) >= 0 && ( it->second.count() - elapsed_time ) < 0 )
    {
      std::cerr << "Start and end time of the communication task are strange." << std::endl;
      std::cerr << __FILE__ << std::endl;
      std::cerr << __LINE__ << std::endl;
    }
    else
    {
    }
  }

  if( 0 <= double( control_end_time.count() - elapsed_time ) && double( control_end_time.count() - elapsed_time ) < max_second_ )
  {
    /* tracking bar */
    cv::line( cv_image, cv::Point( pixel_size * 14 / 20, pixel_size * 2.0 / 20 ), cv::Point( pixel_size * 14 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * 16.0 / 20.0 ) ), line_color, line_thickness * 2, cv::LINE_8 );

    /* tracking end */
    cv::line( cv_image, cv::Point( pixel_size * 13.75 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point(
                pixel_size * 14.25 / 20, pixel_size * ( 2.0 / 20 + double( control_end_time.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), line_color, line_thickness * 2, cv::LINE_8 );
  }
  else if( double( max_second_ ) <= double( control_end_time.count() - elapsed_time ) )
  {
    /* tracking bar */
    cv::line( cv_image, cv::Point( pixel_size * 14 / 20, pixel_size * 2.0 / 20 ), cv::Point( pixel_size * 14 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20 ) ), line_color, line_thickness * 2, cv::LINE_8 );

    /* tracking end */
    cv::line( cv_image, cv::Point( pixel_size * 13.75 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20.0 ) ), cv::Point( pixel_size * 14.25 / 20, pixel_size * ( 2.0 / 20 + 16.0 / 20.0 ) ), line_color, line_thickness * 2, cv::LINE_8 );
  }

  /* tracking gage */
  for( auto it = manual_tracking_durations.begin(); it != manual_tracking_durations.end(); ++it )
  {
    if( ( it->first.count() - elapsed_time ) >= 0 && ( it->second.count() - elapsed_time ) >= 0 )
    {
      if( it->second.count() - elapsed_time < max_second_ )
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 13.5 / 20, pixel_size * ( 2.0 / 20 + double( it->first.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point(
                         pixel_size * 14.5 / 20, pixel_size * ( 2.0 / 20 + double( it->second.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
      else
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 13.5 / 20, pixel_size * ( 2.0 / 20 + double( it->first.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), cv::Point( pixel_size * 14.5 / 20, pixel_size * ( 2.0 / 20 + ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
    }
    else if( ( it->first.count() - elapsed_time ) < 0 && ( it->second.count() - elapsed_time ) >= 0 )
    {
      if( it->second.count() - elapsed_time < max_second_ )
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 13.5 / 20, pixel_size * ( 2.0 / 20 ) ), cv::Point( pixel_size * 14.5 / 20, pixel_size * ( 2.0 / 20 + double( it->second.count() - elapsed_time ) / max_second_ * ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
      else
      {
        cv::rectangle( cv_image, cv::Point( pixel_size * 13.5 / 20, pixel_size * ( 2.0 / 20 ) ), cv::Point( pixel_size * 14.5 / 20, pixel_size * ( 2.0 / 20 + ( 16.0 / 20.0 ) ) ), gage_color, -1, cv::LINE_8 );
      }
    }
    else if( ( it->first.count() - elapsed_time ) < 0 && ( it->second.count() - elapsed_time ) < 0 )
    {
    }
    else if( ( it->first.count() - elapsed_time ) >= 0 && ( it->second.count() - elapsed_time ) < 0 )
    {
      std::cerr << "Start and end time of tracking task is strange." << std::endl;
      std::cerr << __FILE__ << std::endl;
      std::cerr << __LINE__ << std::endl;
    }
    else
    {
    }
  }

  /* frame */
  cv::rectangle( cv_image, cv::Point( pixel_size * 2 / 20, pixel_size * 2.0 / 20 ), cv::Point( pixel_size * 18 / 20, pixel_size * 18.0 / 20 ), line_color, line_thickness, cv::LINE_8 );
  cv::line( cv_image, cv::Point( pixel_size * 10 / 20, pixel_size * 2 / 20 ), cv::Point( pixel_size * 10 / 20, pixel_size * 18 / 20 ), line_color, line_thickness, cv::LINE_8 );

  /* pole */

  for( int i = 1; i < max_min_ * 2; ++i )
  {
    if( i % 2 == 0 )
    {
      cv::line( cv_image, cv::Point( pixel_size * 9.5 / 20, pixel_size * ( 2.0 / 20 + i / ( max_min_ * 2.0 ) * 16.0 / 20.0 ) ), cv::Point( pixel_size * 10.5 / 20, pixel_size * ( 2.0 / 20 + i / ( max_min_ * 2.0 ) * 16.0 / 20.0 ) ), line_color, line_thickness, cv::LINE_8 );
      std::string value_string;
      value_string = std::to_string( i / 2 );
      putText( cv_image, value_string, cv::Point( pixel_size * 11 / 20, pixel_size * ( 2.2 / 20 + i / ( max_min_ * 2.0 ) * 16.0 / 20.0 ) ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 1000, text_color, text_thickness, cv::LINE_AA );
    }
    else
    {
      cv::line( cv_image, cv::Point( pixel_size * 9.75 / 20, pixel_size * ( 2.0 / 20 + i / ( max_min_ * 2.0 ) * 16.0 / 20.0 ) ), cv::Point( pixel_size * 10.25 / 20, pixel_size * ( 2.0 / 20 + i / ( max_min_ * 2.0 ) * 16.0 / 20.0 ) ), line_color, line_thickness, cv::LINE_8 );
    }
  }

}

void SchedulingDisplay::drawElapsedTime()
{
  std::string elapsed_time_string;
  int         seconds = MatbEventServer::elapsed_time() / 1000000000 % 60;
  int         minutes = MatbEventServer::elapsed_time() / 1000000000 / 60 % 60;
  std::string minutes_string;

  if( minutes < 10 )
  {
    minutes_string = "0" + std::to_string( minutes );
  }
  else
  {
    minutes_string = std::to_string( minutes );
  }

  std::string seconds_string;

  if( seconds < 10 )
  {
    seconds_string = "0" + std::to_string( seconds );
  }
  else
  {
    seconds_string = std::to_string( seconds );
  }

  elapsed_time_string = elapsed_time_string + "Elapsed Time  ";
  elapsed_time_string = elapsed_time_string + minutes_string + ":" + seconds_string;
  putText( cv_image, elapsed_time_string, cv::Point( pixel_size * 5 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
}

void SchedulingDisplay::takeInEachTaskStartAndEndTime()
{
  std::chrono::seconds tracking_start_time;
  std::chrono::seconds tracking_end_time;
  std::chrono::seconds communication_task_start_time;
  std::chrono::seconds communication_task_stop_time;

  for( auto it = system_events_.begin(); it != system_events_.end(); ++it )
  {
    if( SystemEvent::Control::START == it->get()->control() )
    {
      control_start_time = it->get()->start_time();
    }

    if( SystemEvent::Control::END == it->get()->control() )
    {
      control_end_time = it->get()->start_time();
    }
  }

  for( auto it = scheduling_events_.begin(); it != scheduling_events_.end(); ++it )
  {
    if( SchedulingEvent::Task::COMM == it->get()->task() )
    {
      if( SchedulingEvent::Action::START == it->get()->action() )
      {
        communication_task_start_time = it->get()->start_time();
      }
      else if( SchedulingEvent::Action::STOP == it->get()->action() )
      {
        communication_task_stop_time = it->get()->start_time();
        communication_task_durations.emplace_back( std::make_pair( communication_task_start_time, communication_task_stop_time ) );
      }
      else
      {
      }
    }
    else if( SchedulingEvent::Task::RESMAN == it->get()->task() )
    {
      if( SchedulingEvent::Action::START == it->get()->action() )
      {
        resource_management_task_start_time = it->get()->start_time();
      }
      else if( SchedulingEvent::Action::STOP == it->get()->action() )
      {
        resource_management_task_stop_time = it->get()->start_time();
      }
      else
      {
      }
    }
    else if( SchedulingEvent::Task::SYSMON == it->get()->task() )
    {
      if( SchedulingEvent::Action::START == it->get()->action() )
      {
        system_monitoring_task_start_time = it->get()->start_time();
      }
      else if( SchedulingEvent::Action::STOP == it->get()->action() )
      {
        system_monitoring_task_stop_time = it->get()->start_time();;
      }
      else
      {
      }
    }
    else if( SchedulingEvent::Task::RESSYS == it->get()->task() )
    {
      if( SchedulingEvent::Action::START == it->get()->action() )
      {
        resource_management_task_start_time = it->get()->start_time();
        system_monitoring_task_start_time   = it->get()->start_time();
      }
      else if( SchedulingEvent::Action::STOP == it->get()->action() )
      {
        resource_management_task_stop_time = it->get()->start_time();
        system_monitoring_task_stop_time   = it->get()->start_time();
      }
      else
      {
      }
    }
    else if( SchedulingEvent::Task::TRACK == it->get()->task() )
    {
      if( SchedulingEvent::Action::MANUAL == it->get()->action() )
      {
        tracking_start_time = it->get()->start_time();
      }
      else if( SchedulingEvent::Action::AUTO == it->get()->action() )
      {
        tracking_end_time = it->get()->start_time();
        manual_tracking_durations.emplace_back( std::make_pair( tracking_start_time, tracking_end_time ) );
      }
      else
      {
      }
    }
    else
    {
    }
  }
}



};







