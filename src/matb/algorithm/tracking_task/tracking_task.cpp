#include "tracking_task.hpp"
namespace matb
{
  TrackingTask::TrackingTask()
  {
    out_of_track_timer.stop();
    std::srand( std::time( 0 ) );
    mt19937             = std::mt19937( random_device() );
    //   uniform_int_distribution =  std::uniform_int_distribution<>( -10, 10 );
    normal_distribution = std::normal_distribution<>( 0, standard_deviation );
    line_color          = cv::Scalar( 150, 50, 0 );
    text_color          = cv::Scalar( 150, 50, 0 );
    arrow_color         = cv::Scalar( 255, 50, 0 );
    pole_color          = cv::Scalar( 255, 200, 150 );

    cv_target_point.x = pixel_size / 2 * ( 1 + x1 );
    cv_target_point.y = pixel_size / 2 * ( 1 - y1 );
  }

  TrackingTask::~TrackingTask()
  {
  }

  void TrackingTask::start()
  {
    scheduling_events_ = MatbEventServer::scheduling_events();
//     is_manual_mode     = true;
    is_started         = true;
  }

  void TrackingTask::stop()
  {
    is_started = false;
  }

  void TrackingTask::update()
  {
    if( is_started )
    {
      updateMatbEvents();
      updateTargetValue();
    }

    draw();
  }

  void TrackingTask::updateTargetValue()
  {
    /* out_of_track_timer that is used for publisher */
    if( x0 < -0.25 || 0.25 < x0 || y0 < -0.25 || 0.25 < y0 )
    {
      if( out_of_track_timer.is_stopped() )
      {
        out_of_track_timer.start();
      }
    }
    else
    {
      out_of_track_timer.stop();
    }

    /* update values from joystick input + gausian random values */
    if( !considered_dynamics_ )
    {
      x1 = x0 + joystick_x_ * joystick_gain + normal_distribution( mt19937 );
      y1 = y0 + joystick_y_ * joystick_gain + normal_distribution( mt19937 );
    }
    else
    {
      /* caluculate new values */
//     x1 = x0 + v0 * frequency_;
//     v1 = v0 + a0 * frequency_;
//     a1 = gravity * x0 - ( joystick_x_ * joystick_gain + normal_distribution( mt19937 ) - viscocity * v1 );
//     y1 = y0 + w0 * frequency_;
//     w1 = w0 + b0 * frequency_;
//     b1 = gravity * y0 - ( joystick_y_ * joystick_gain + normal_distribution( mt19937 ) - viscocity * w1 );
    }

    /* barrier at -1 and +1 */
    if( x1 >= unit_norm )
    {
      x1 = unit_norm;
    }
    else if( x1 <= -unit_norm )
    {
      x1 = -unit_norm;
    }
    else
    {
    }

    if( y1 >= unit_norm )
    {
      y1 = unit_norm;
    }
    else if( y1 <= -unit_norm )
    {
      y1 = -unit_norm;
    }
    else
    {
    }

    /* check manual or auto*/
    if( is_manual_mode )
    {
    }
    else
    {
      /* Automatic Mode */
      x1 = 0;
      v1 = 0;
      a1 = 0;
      y1 = 0;
      w1 = 0;
      b1 = 0;
    }

    /* mapping to pixel image */
    cv_target_point.x = pixel_size / 2 * ( 1 + x1 );
    cv_target_point.y = pixel_size / 2 * ( 1 - y1 );
    /* copy latest values */
    x0 = x1;
    y0 = y1;


  }

  void TrackingTask::drawTarget()
  {
    cv::Scalar target_color( 255, 200, 0 );

//   if( std::sqrt( x1 * x1 + y1 * y1 ) > 0.8 )
//   {
//     target_color = cv::Scalar( 0, 50, 255 );
//   }

    cv::circle( cv_image, cv_target_point, radius_of_target, target_color, target_thickness );
    cv::circle( cv_image, cv_target_point, 3, target_color, -1 );
    cv::line( cv_image, cv_target_point + cv::Point( 0, 0.5 * radius_of_target ), cv_target_point + cv::Point( 0, radius_of_target ), target_color, target_thickness, cv::LINE_8 );
    cv::line( cv_image, cv_target_point + cv::Point( 0, -0.5 * radius_of_target ), cv_target_point + cv::Point( 0, -radius_of_target ), target_color, target_thickness, cv::LINE_8 );
    cv::line( cv_image, cv_target_point + cv::Point( 0.5 * radius_of_target, 0 ), cv_target_point + cv::Point( radius_of_target, 0 ), target_color, target_thickness, cv::LINE_8 );
    cv::line( cv_image, cv_target_point + cv::Point( -0.5 * radius_of_target, 0 ), cv_target_point + cv::Point( -radius_of_target, 0 ), target_color, target_thickness, cv::LINE_8 );

    /* arrow */
    cv::line( cv_image, cv_target_point, cv_target_point + cv::Point( joystick_x_ * pixel_size * 0.1, -joystick_y_ * pixel_size * 0.1 ), arrow_color, target_thickness, cv::LINE_8 );
    cv::circle( cv_image, cv_target_point + cv::Point( joystick_x_ * pixel_size * 0.1, -joystick_y_ * pixel_size * 0.1 ), pixel_size * 5 / 500, arrow_color, -1 );
  }

  void TrackingTask::updateMatbEvents()
  {
    for( auto it = scheduling_events_.begin(); it != scheduling_events_.end(); ++it )
    {
      if( !it->get()->checkDone() )
      {
        if( SchedulingEvent::Task::TRACK == it->get()->task() )
        {
          auto elapsed_time = MatbEventServer::elapsed_time();
          auto event_time   = std::chrono::duration_cast< std::chrono::nanoseconds >( it->get()->start_time() ).count();

          if( ( elapsed_time - event_time ) >= 0 )
          {
            if( SchedulingEvent::Action::MANUAL == it->get()->action() )
            {
              is_manual_mode = true;
              it->get()->done();

              if( SchedulingEvent::Update::LOW == it->get()->update() )
              {
                update_value = LowMediumHigh::LOW;
              }
              else if( SchedulingEvent::Update::MEDIUM == it->get()->update() )
              {
                update_value = LowMediumHigh::MEDIUM;
              }
              else if( SchedulingEvent::Update::HIGH == it->get()->update() )
              {
                update_value = LowMediumHigh::HIGH;
              }
              else
              {
              }

              if( SchedulingEvent::Update::LOW == it->get()->update() )
              {
                response_value = LowMediumHigh::LOW;
              }

              if( SchedulingEvent::Update::MEDIUM == it->get()->update() )
              {
                response_value = LowMediumHigh::MEDIUM;
              }

              if( SchedulingEvent::Update::HIGH == it->get()->update() )
              {
                response_value = LowMediumHigh::HIGH;
              }
              else
              {
              }
            }
            else if( SchedulingEvent::Action::AUTO == it->get()->action() )
            {
              is_manual_mode = false;
              it->get()->done();
            }
            else
            {
            }
          }
          else
          {
          }

          break;
        }
        else
        {
        }
      }
    }
  }

  void TrackingTask::draw()
  {
    cv_image = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );
    drawGrid();
    drawTarget();
    drawText();
  }

  void TrackingTask::drawText()
  {
    std::string manual_or_auto;
    int         text_thickness = 1;

    if( is_manual_mode )
    {
      manual_or_auto = "MANUAL MODE";
    }
    else
    {
      manual_or_auto = "AUTOMATIC MODE";
    }

    putText( cv_image, manual_or_auto, cv::Point( pixel_size * 12 / 20, pixel_size * 18 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 900, text_color, text_thickness, cv::LINE_AA );
    std::ostringstream stream_x;
    stream_x << std::fixed;
    stream_x << std::setprecision( 2 );
    stream_x << x1;
    std::string        cordinate_value_x = stream_x.str();
    std::ostringstream stream_y;
    stream_y << std::fixed;
    stream_y << std::setprecision( 2 );
    stream_y << y1;
    std::string cordinate_value_y       = stream_y.str();
    std::string cordinate_value_x_and_y = "(x, y) = (" + cordinate_value_x + ", " + cordinate_value_y + ")";
    putText( cv_image, cordinate_value_x_and_y, cv::Point( pixel_size * 11 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 900, text_color, text_thickness, cv::LINE_AA );
  }

  void TrackingTask::drawChainLine( cv::Mat img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, int thickness, int lineType, int shift )
  {
    cv::LineIterator it( img, pt1, pt2, 8 );

    for( int i = 0; i < it.count; i++, it++ )
    {
      if( i % 10 == 0 || i % 10 == 1 || i % 10 == 2 || i % 10 == 3 || i % 10 == 6 || i % 10 == 7 )
      {
        ( *it )[0] = color[0]; // Blue
        ( *it )[1] = color[1]; // Green
        ( *it )[2] = color[2]; // Red
      }
      else
      {
      }
    }
  }

  void TrackingTask::drawGrid()
  {
    /*  */

    /* frame */
    cv::line( cv_image, cv::Point( 0, 0 ), cv::Point( pixel_size * 1 / 8, 0 ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 7 / 8, 0 ), cv::Point( pixel_size, 0 ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size, 0 ), cv::Point( pixel_size, pixel_size * 1 / 8 ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size, pixel_size * 7 / 8 ), cv::Point( pixel_size, pixel_size ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size, pixel_size ), cv::Point( pixel_size * 7 / 8, pixel_size ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 1 / 8, pixel_size ), cv::Point( 0, pixel_size ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( 0, pixel_size ), cv::Point( 0, pixel_size * 7 / 8 ), pole_color, 4, cv::LINE_8 );
    cv::line( cv_image, cv::Point( 0, pixel_size * 1 / 8 ), cv::Point( 0, 0 ), pole_color, 4, cv::LINE_8 );

    /* x pole */
    cv::line( cv_image, cv::Point( 0, pixel_size / 2 ), cv::Point( pixel_size, pixel_size / 2 ), pole_color, 2, cv::LINE_8 );

    /* x pole grid */
    cv::line( cv_image, cv::Point( 0, pixel_size * 7 / 16 ), cv::Point( 0, pixel_size * 9 / 16 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 1 / 8, pixel_size * 19 / 40 ), cv::Point( pixel_size * 1 / 8, pixel_size * 21 / 40 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 1 / 4, pixel_size * 7 / 16 ), cv::Point( pixel_size * 1 / 4, pixel_size * 9 / 16 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 3 / 4, pixel_size * 7 / 16 ), cv::Point( pixel_size * 3 / 4, pixel_size * 9 / 16 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 7 / 8, pixel_size * 19 / 40 ), cv::Point( pixel_size * 7 / 8, pixel_size * 21 / 40 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size, pixel_size * 7 / 16 ), cv::Point( pixel_size, pixel_size * 9 / 16 ), pole_color, 2, cv::LINE_8 );

    /* y pole */
    cv::line( cv_image, cv::Point( pixel_size / 2, 0 ), cv::Point( pixel_size / 2, pixel_size ), pole_color, 2, cv::LINE_8 );

    /* y pole grid */
    cv::line( cv_image, cv::Point( pixel_size * 7 / 16, 0 ), cv::Point( pixel_size * 9 / 16, 0 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 19 / 40, pixel_size * 1 / 8 ), cv::Point( pixel_size * 21 / 40, pixel_size * 1 / 8 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 7 / 16, pixel_size * 1 / 4 ), cv::Point( pixel_size * 9 / 16, pixel_size * 1 / 4 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 7 / 16, pixel_size * 3 / 4 ), cv::Point( pixel_size * 9 / 16, pixel_size * 3 / 4 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 19 / 40, pixel_size * 7 / 8 ), cv::Point( pixel_size * 21 / 40, pixel_size * 7 / 8 ), pole_color, 2, cv::LINE_8 );
    cv::line( cv_image, cv::Point( pixel_size * 7 / 16, pixel_size ), cv::Point( pixel_size * 9 / 16, pixel_size ), pole_color, 2, cv::LINE_8 );

    /* center box*/

    drawChainLine( cv_image, cv::Point( pixel_size * 3 / 8, pixel_size * 3 / 8 ), cv::Point( pixel_size * 5 / 8, pixel_size * 3 / 8 ), pole_color, 2, cv::LINE_8 );
    drawChainLine( cv_image, cv::Point( pixel_size * 5 / 8, pixel_size * 3 / 8 ), cv::Point( pixel_size * 5 / 8, pixel_size * 5 / 8 ), pole_color, 2, cv::LINE_8 );
    drawChainLine( cv_image, cv::Point( pixel_size * 5 / 8, pixel_size * 5 / 8 ), cv::Point( pixel_size * 3 / 8, pixel_size * 5 / 8 ), pole_color, 2, cv::LINE_8 );
    drawChainLine( cv_image, cv::Point( pixel_size * 3 / 8, pixel_size * 5 / 8 ), cv::Point( pixel_size * 3 / 8, pixel_size * 3 / 8 ), pole_color, 2, cv::LINE_8 );

    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.1, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.2, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.3, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.4, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.5, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.6, pole_color, 1 );
    //   cv::circle( cv_image, cv::Point( pixel_size / 2, pixel_size / 2 ), pixel_size * 0.8, pole_color, 1 );

  }
};
