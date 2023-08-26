#include "system_monitoring_task.hpp"
namespace matb
{
  SystemMonitoringTask::SystemMonitoringTask()
  {
    f1_timer_.stop();
    f2_timer_.stop();
    f3_timer_.stop();
    f4_timer_.stop();
    f5_timer_.stop();
    f6_timer_.stop();
    system_monitoring_events_ = MatbEventServer::system_monitoring_events();
    mt19937                   = std::mt19937( random_device() );
    uniform_int_distribution  = std::uniform_int_distribution<>( -1, 1 );
    line_color                = cv::Scalar( 150, 50, 0 );
    text_color                = cv::Scalar( 150, 50, 0 );
    sky_blue                  = cv::Scalar( 255, 255, 150 );
    dark_blue                 = cv::Scalar( 255, 150, 0 );
  }

  SystemMonitoringTask::~SystemMonitoringTask()
  {
  }

  void SystemMonitoringTask::start()
  {
    is_started = true;
  }

  void SystemMonitoringTask::stop()
  {
    is_started = false;
  }

  void SystemMonitoringTask::update()
  {
    if( is_started )
    {
      updateMatbEvent();

      if( 0 == ++update_counter_ % 6 )
      {
        position_f1_ = base_position_f1_ + uniform_int_distribution( mt19937 );
        position_f2_ = base_position_f2_ + uniform_int_distribution( mt19937 );
        position_f3_ = base_position_f3_ + uniform_int_distribution( mt19937 );
        position_f4_ = base_position_f4_ + uniform_int_distribution( mt19937 );
      }
    }

    draw();
  }

  void SystemMonitoringTask::draw()
  {
    cv_image = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );

    if( button_a_ || 65470 == native_virtual_key_ )
    {
      base_position_f1_ = 0;
      f1_timer_.stop();
    }

    if( button_b_ || 65471 == native_virtual_key_ )
    {
      base_position_f2_ = 0;
      f2_timer_.stop();
    }

    if( button_x_ || 65472 == native_virtual_key_ )
    {
      base_position_f3_ = 0;
      f3_timer_.stop();
    }

    if( button_y_ || 65473 == native_virtual_key_ )
    {
      base_position_f4_ = 0;
      f4_timer_.stop();
    }

    if( button_lb_ || 65474 == native_virtual_key_ )
    {
      is_green_ = true;
      f5_timer_.stop();
    }

    if( button_rb_ || 65475 == native_virtual_key_ )
    {
      is_red_ = false;
      f6_timer_.stop();
    }

    /* F5 */
    if( is_green_ )
    {
      cv::rectangle( cv_image, cv::Point( pixel_size * 1 / 16, pixel_size * 1 / 16 ), cv::Point( pixel_size * 6 / 16, pixel_size * 3 / 16 ), cv::Scalar( 0, 255, 0 ), -1, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 1 / 16, pixel_size * 1 / 16 ), cv::Point( pixel_size * 6 / 16, pixel_size * 3 / 16 ), line_color, line_thickness, cv::LINE_8 );
    putText( cv_image, "F5", cv::Point( pixel_size * 3 / 16, pixel_size * 2.3 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    /* F6 */
    if( is_red_ )
    {
      cv::rectangle( cv_image, cv::Point( pixel_size * 10 / 16, pixel_size * 1 / 16 ), cv::Point( pixel_size * 15 / 16, pixel_size * 3 / 16 ), cv::Scalar( 0, 0, 255 ), -1, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 10 / 16, pixel_size * 1 / 16 ), cv::Point( pixel_size * 15 / 16, pixel_size * 3 / 16 ), line_color, line_thickness, cv::LINE_8 );
    putText( cv_image, "F6", cv::Point( pixel_size * 12 / 16, pixel_size * 2.3 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    /* F1 */
    for( auto i = 0; i < 11; ++i )
    {
      cv::Scalar inside_color;

      if( 5 + position_f1_ == i || 5 + position_f1_ - 1 == i || 5 + position_f1_ + 1 == i )
      {
        inside_color = dark_blue;
      }
      else
      {
        inside_color = sky_blue;
      }

      cv::rectangle( cv_image, cv::Point( pixel_size * 1 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 3 / 16, pixel_size * ( 5 + i ) / 16 ), inside_color, -1, cv::LINE_8 );
      cv::rectangle( cv_image, cv::Point( pixel_size * 1 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 3 / 16, pixel_size * ( 5 + i ) / 16 ), line_color, line_thickness, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 1 / 16, pixel_size * ( 7 ) / 16 ), cv::Point( pixel_size * 3 / 16, pixel_size * ( 12 ) / 16 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( cv_image, "F1", cv::Point( pixel_size * 1.5 / 16, pixel_size * 15.7 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    /* F2 */
    for( auto i = 0; i < 11; ++i )
    {
      cv::Scalar inside_color;

      if( 5 + position_f2_ == i || 5 + position_f2_ - 1 == i || 5 + position_f2_ + 1 == i )
      {
        inside_color = dark_blue;
      }
      else
      {
        inside_color = sky_blue;
      }

      cv::rectangle( cv_image, cv::Point( pixel_size * 5 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 7 / 16, pixel_size * ( 5 + i ) / 16 ), inside_color, -1, cv::LINE_8 );
      cv::rectangle( cv_image, cv::Point( pixel_size * 5 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 7 / 16, pixel_size * ( 5 + i ) / 16 ), line_color, line_thickness, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 5 / 16, pixel_size * ( 7 ) / 16 ), cv::Point( pixel_size * 7 / 16, pixel_size * ( 12 ) / 16 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( cv_image, "F2", cv::Point( pixel_size * 5.5 / 16, pixel_size * 15.7 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    /* F3 */
    for( auto i = 0; i < 11; ++i )
    {
      cv::Scalar inside_color;

      if( 5 + position_f3_ == i || 5 + position_f3_ - 1 == i || 5 + position_f3_ + 1 == i )
      {
        inside_color = dark_blue;
      }
      else
      {
        inside_color = sky_blue;
      }

      cv::rectangle( cv_image, cv::Point( pixel_size * 9 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 11 / 16, pixel_size * ( 5 + i ) / 16 ), inside_color, -1, cv::LINE_8 );
      cv::rectangle( cv_image, cv::Point( pixel_size * 9 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 11 / 16, pixel_size * ( 5 + i ) / 16 ), line_color, line_thickness, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 9 / 16, pixel_size * 7 / 16 ), cv::Point( pixel_size * 11 / 16, pixel_size * 12 / 16 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( cv_image, "F3", cv::Point( pixel_size * 9.5 / 16, pixel_size * 15.7 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    /* F4 */
    for( auto i = 0; i < 11; ++i )
    {
      cv::Scalar inside_color;

      if( 5 + position_f4_ == i || 5 + position_f4_ - 1 == i || 5 + position_f4_ + 1 == i )
      {
        inside_color = dark_blue;
      }
      else
      {
        inside_color = sky_blue;
      }

      cv::rectangle( cv_image, cv::Point( pixel_size * 13 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 15 / 16, pixel_size * ( 5 + i ) / 16 ), inside_color, -1, cv::LINE_8 );
      cv::rectangle( cv_image, cv::Point( pixel_size * 13 / 16, pixel_size * ( 4 + i ) / 16 ), cv::Point( pixel_size * 15 / 16, pixel_size * ( 5 + i ) / 16 ), line_color, line_thickness, cv::LINE_8 );
    }

    cv::rectangle( cv_image, cv::Point( pixel_size * 13 / 16, pixel_size * 7 / 16 ), cv::Point( pixel_size * 15 / 16, pixel_size * 12 / 16 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( cv_image, "F4", cv::Point( pixel_size * 13.5 / 16, pixel_size * 15.7 / 16 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
  }

  void SystemMonitoringTask::updateMatbEvent()
  {
    for( auto it = system_monitoring_events_.begin(); it != system_monitoring_events_.end(); ++it )
    {
      if( it->get()->checkDone() )
      {
      }
      else
      {
        auto elapsed_time = MatbEventServer::elapsed_time();
        auto event_time   = std::chrono::duration_cast< std::chrono::nanoseconds >( it->get()->start_time() ).count();

        if( ( elapsed_time - event_time ) >= 0 )
        {
          it->get()->done();

          if( SystemMonitoringEvent::MonitoringLightType::GREEN == it->get()->monitoring_light_type() )
          {
            f5_timer_.start();
            is_green_ = false;
          }
          else if( SystemMonitoringEvent::MonitoringLightType::RED == it->get()->monitoring_light_type() )
          {
            f6_timer_.start();
            is_red_ = true;
          }
          else
          {
          }

          if( SystemMonitoringEvent::MonitoringScaleNumber::ONE == it->get()->monitoring_scale_number() )
          {
            f1_timer_.start();

            if( SystemMonitoringEvent::MonitoringScaleDirection::UP == it->get()->monitoring_scale_direction() )
            {
              base_position_f1_ = 3;
            }
            else if( SystemMonitoringEvent::MonitoringScaleDirection::DOWN == it->get()->monitoring_scale_direction() )
            {
              base_position_f1_ = -3;
            }
            else
            {
            }
          }
          else if( SystemMonitoringEvent::MonitoringScaleNumber::TWO == it->get()->monitoring_scale_number() )
          {
            f2_timer_.start();

            if( SystemMonitoringEvent::MonitoringScaleDirection::UP == it->get()->monitoring_scale_direction() )
            {
              base_position_f2_ = 3;
            }
            else if( SystemMonitoringEvent::MonitoringScaleDirection::DOWN == it->get()->monitoring_scale_direction() )
            {
              base_position_f2_ = -3;
            }
            else
            {
            }
          }
          else if( SystemMonitoringEvent::MonitoringScaleNumber::THREE == it->get()->monitoring_scale_number() )
          {
            f3_timer_.start();

            if( SystemMonitoringEvent::MonitoringScaleDirection::UP == it->get()->monitoring_scale_direction() )
            {
              base_position_f3_ = 3;
            }
            else if( SystemMonitoringEvent::MonitoringScaleDirection::DOWN == it->get()->monitoring_scale_direction() )
            {
              base_position_f3_ = -3;
            }
            else
            {
            }
          }
          else if( SystemMonitoringEvent::MonitoringScaleNumber::FOUR == it->get()->monitoring_scale_number() )
          {
            f4_timer_.start();

            if( SystemMonitoringEvent::MonitoringScaleDirection::UP == it->get()->monitoring_scale_direction() )
            {
              base_position_f4_ = 3;
            }
            else if( SystemMonitoringEvent::MonitoringScaleDirection::DOWN == it->get()->monitoring_scale_direction() )
            {
              base_position_f4_ = -3;
              std::cout << "sysmon modulethread at line " << __LINE__ << std::endl; /* to avoid error to open image port ??? */
            }
            else
            {
            }
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
  }
};




