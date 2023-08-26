#include "resource_management_task_thread.hpp"

namespace matb
{

  ResourceManagementTaskThread::ResourceManagementTaskThread( const double& _period, yarp::os::ResourceFinder& _rf ) : PeriodicThread( _period )
  {
    rf_ = _rf;
  }

  ResourceManagementTaskThread::~ResourceManagementTaskThread()
  {
  }

  bool ResourceManagementTaskThread::threadInit()
  {
    /* subscriber */
    key_press_event_subscriber_port_.useCallback( key_press_event_subscriber_ );
    key_press_event_subscriber_port_.setReplier( key_press_event_subscriber_ );
    key_press_event_subscriber_port_.open( "/" + rf_.find( "name" ).asString() + "/resman_task/key_press_event/sub" );

    /* publisher */
    resman_image_publisher_buffered_port_.open( "/" + rf_.find( "name" ).asString() + "/resman_task/image/pub" );
    pump_status_image_buffered_port_.open( "/" + rf_.find( "name" ).asString() + "/resman_task/pump_status/image/pub" );
    resman_status_publisher_port_.open( "/" + rf_.find( "name" ).asString() + "/resman_task/resman_status/pub" );
    return true;
  }

  void ResourceManagementTaskThread::threadRelease()
  {
    //   /* subscriber */
    key_press_event_subscriber_port_.close();
    //   /* publisher */
    resman_image_publisher_buffered_port_.close();
    pump_status_image_buffered_port_.close();
    resman_status_publisher_port_.close();
    std::cout << "Calling close function in ResourceManagementTaskThread\n";
    return;
  }

  void ResourceManagementTaskThread::afterStart( bool _success )
  {
  }

  void ResourceManagementTaskThread::run()
  {
    input();
    update();
    output();
  }

  void ResourceManagementTaskThread::input()
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
  }

  void ResourceManagementTaskThread::output()
  {
    yarp::rosmsg::matb_msgs::Resman resman_message;
    resman_message.elapsed_time      = MatbEventServer::elapsed_time();
    resman_message.amount_of_tank_A  = amount_of_tank_A;
    resman_message.amount_of_tank_B  = amount_of_tank_B;
    resman_message.amount_of_tank_C  = amount_of_tank_C;
    resman_message.amount_of_tank_D  = amount_of_tank_D;
    resman_message.valve_1_is_failed = valve_1_is_failed;
    resman_message.valve_2_is_failed = valve_2_is_failed;
    resman_message.valve_3_is_failed = valve_3_is_failed;
    resman_message.valve_4_is_failed = valve_4_is_failed;
    resman_message.valve_5_is_failed = valve_5_is_failed;
    resman_message.valve_6_is_failed = valve_6_is_failed;
    resman_message.valve_7_is_failed = valve_7_is_failed;
    resman_message.valve_8_is_failed = valve_8_is_failed;
    resman_message.valve_1_is_on     = valve_1_is_on;
    resman_message.valve_2_is_on     = valve_2_is_on;
    resman_message.valve_3_is_on     = valve_3_is_on;
    resman_message.valve_4_is_on     = valve_4_is_on;
    resman_message.valve_5_is_on     = valve_5_is_on;
    resman_message.valve_6_is_on     = valve_6_is_on;
    resman_message.valve_7_is_on     = valve_7_is_on;
    resman_message.valve_8_is_on     = valve_8_is_on;
    resman_status_publisher_port_.prepare() = resman_message;
    resman_status_publisher_port_.write();

    if( tank_A_timer_.is_stopped() )
    {
      resman_message.tank_A_elapsed_time = 0;
    }
    else
    {
      resman_message.tank_A_elapsed_time = tank_A_timer_.elapsed().wall;
    }

    if( tank_B_timer_.is_stopped() )
    {
      resman_message.tank_B_elapsed_time = 0;
    }
    else
    {
      resman_message.tank_B_elapsed_time = tank_B_timer_.elapsed().wall;
    }

    resman_image_publisher_buffered_port_.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( resman_cv_image_ );
    resman_image_publisher_buffered_port_.write();
    pump_status_image_buffered_port_.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( pump_status_cv_image_ );
    pump_status_image_buffered_port_.write();
  }

};

