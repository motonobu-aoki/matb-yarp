#include "system_monitoring_task_thread.hpp"
namespace matb
{
  SystemMonitoringTaskThread::SystemMonitoringTaskThread( const double& _period, yarp::os::ResourceFinder& _rf ) : PeriodicThread( _period )
  {
    rf_ = _rf;
  }

  SystemMonitoringTaskThread::~SystemMonitoringTaskThread()
  {
  }

  bool SystemMonitoringTaskThread::threadInit()
  {
    /* subscriber */
    key_press_event_subscriber_port_.useCallback( key_press_event_subscriber_ );
    key_press_event_subscriber_port_.setReplier( key_press_event_subscriber_ );
    key_press_event_subscriber_port_.open( "/" + rf_.find( "name" ).asString() + "/sysmon_task/key_press_event/sub" );
    joystick_button_subscriber_port.useCallback( joystick_button_subscriber );
    joystick_button_subscriber_port.setReplier( joystick_button_subscriber );
    joystick_button_subscriber_port.open( "/" + rf_.find( "name" ).asString() + "/sysmon_task/joystick_button/sub" );

    /* publisher */
    image_buffered_port.open( "/" + rf_.find( "name" ).asString() + "/sysmon_task/image/pub" );
    system_monitoring_task_publisher_port_.open( "/" + rf_.find( "name" ).asString() + "/sysmon_task/sysmon_status/pub" );
    return true;
  }

  void SystemMonitoringTaskThread::threadRelease()
  {
    /* subscriber */
    key_press_event_subscriber_port_.close();
    joystick_button_subscriber_port.close();
    /* publisher */
    image_buffered_port.close();
    system_monitoring_task_publisher_port_.close();
    std::cout << "Calling close function in SystemMonitoringTaskThread\n";
    return;
  }

  void SystemMonitoringTaskThread::afterStart( bool _success )
  {
  }

  void SystemMonitoringTaskThread::run()
  {
    input();
    update();
    output();
  }

  void SystemMonitoringTaskThread::input()
  {
    auto key_press_event = key_press_event_subscriber_.bottle();

    if( key_press_event.is_auto_repeat )
    {
      native_virtual_key_ = -1;
    }
    else
    {
      if( key_press_event.timestamp == last_key_press_time_stamp )
      {
        native_virtual_key_ = -1;
      }
      else
      {
        native_virtual_key_ = key_press_event.native_virtual_key;
      }
    }

    last_key_press_time_stamp = key_press_event.timestamp;
    button_a_                 = joystick_button_subscriber.a();
    button_b_                 = joystick_button_subscriber.b();
    button_x_                 = joystick_button_subscriber.x();
    button_y_                 = joystick_button_subscriber.y();
    button_lb_                = joystick_button_subscriber.lb();
    button_rb_                = joystick_button_subscriber.rb();
  }

  void SystemMonitoringTaskThread::output()
  {
    image_buffered_port.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( cv_image );
    image_buffered_port.write();
    yarp::rosmsg::matb_msgs::Sysmon sysmon_message;
    sysmon_message.pressed_key = "";
    sysmon_message.base_position_f1 = base_position_f1_;
    sysmon_message.base_position_f2 = base_position_f2_;
    sysmon_message.base_position_f3 = base_position_f3_;
    sysmon_message.base_position_f4 = base_position_f4_;
    sysmon_message.is_green         = is_green_;
    sysmon_message.is_red           = is_red_;
    sysmon_message.position_f1      = position_f1_;
    sysmon_message.position_f2      = position_f2_;
    sysmon_message.position_f3      = position_f3_;
    sysmon_message.position_f4      = position_f4_;
    sysmon_message.elapsed_time      = MatbEventServer::elapsed_time();

    if( f1_timer_.is_stopped() )
    {
      sysmon_message.f1_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f1_elapsed_time = f1_timer_.elapsed().wall;
    }

    if( f2_timer_.is_stopped() )
    {
      sysmon_message.f2_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f2_elapsed_time = f2_timer_.elapsed().wall;
    }

    if( f3_timer_.is_stopped() )
    {
      sysmon_message.f3_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f3_elapsed_time = f3_timer_.elapsed().wall;
    }

    if( f4_timer_.is_stopped() )
    {
      sysmon_message.f4_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f4_elapsed_time = f4_timer_.elapsed().wall;
    }

    if( f5_timer_.is_stopped() )
    {
      sysmon_message.f5_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f5_elapsed_time = f5_timer_.elapsed().wall;
    }

    if( f6_timer_.is_stopped() )
    {
      sysmon_message.f6_elapsed_time = 0;
    }
    else
    {
      sysmon_message.f6_elapsed_time = f6_timer_.elapsed().wall;
    }

    sysmon_message.pressed_key = "";

    if( button_a_ || 65470 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F1";
    }

    if( button_b_ || 65471 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F2";
    }

    if( button_x_ || 65472 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F3";
    }

    if( button_y_ || 65473 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F4";
    }

    if( button_lb_ || 65474 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F5";
    }

    if( button_rb_ || 65475 == native_virtual_key_ )
    {
      sysmon_message.pressed_key = "F6";
    }



    system_monitoring_task_publisher_port_.prepare() = sysmon_message;
    system_monitoring_task_publisher_port_.write();
  }

};
