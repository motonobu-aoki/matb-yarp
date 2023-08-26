#include "communications_task_thread.hpp"

namespace matb
{

  CommunicationsTaskThread::CommunicationsTaskThread( double _period, yarp::os::ResourceFinder& _rf ) : yarp::os::PeriodicThread( _period )
  {
    rf_ = _rf;
  }

  CommunicationsTaskThread::~CommunicationsTaskThread()
  {
  }

  bool CommunicationsTaskThread::threadInit()
  {
    /* subscriber */
    joystick_button_subscriber_port.useCallback( joystick_button_subscriber );
    joystick_button_subscriber_port.setReplier( joystick_button_subscriber );

    if( !joystick_button_subscriber_port.open( "/" + rf_.find( "name" ).asString() + "/communications_task/joystick_button/sub" ) )
    {
      return false;
    }

    key_press_event_subscriber_port_.useCallback( key_press_event_subscriber_ );
    key_press_event_subscriber_port_.setReplier( key_press_event_subscriber_ );

    if( !key_press_event_subscriber_port_.open( "/" + rf_.find( "name" ).asString() + "/communications_task/key_press_event/sub" ) )
    {
      return false;
    }


    key_release_event_subscriber_port_.useCallback( key_release_event_subscriber_ );
    key_release_event_subscriber_port_.setReplier( key_release_event_subscriber_ );

    if( !key_release_event_subscriber_port_.open( "/" + rf_.find( "name" ).asString() + "/communications_task/key_release_event/sub" ) )
    {
      return false;
    }

    /* publisher */
    if( !speech_client_port.open( "/" + rf_.find( "name" ).asString() + "/communications_task/instruction/pub" ) )
    {
      return false;
    }

    if( !buffered_port.open( "/" + rf_.find( "name" ).asString() + "/communications_task/image/pub" ) )
    {
      return false;
    }

    if( !communication_task_status_publisher_port.open( "/" + rf_.find( "name" ).asString() + "/communications_task/communication_status/pub" ) )
    {
      return false;
    }

    return true;
  }

  void CommunicationsTaskThread::threadRelease()
  {
    /* subscriber */
    joystick_button_subscriber_port.close();
    key_press_event_subscriber_port_.close();
    key_release_event_subscriber_port_.close();
    /* publisher */
    speech_client_port.close();
    buffered_port.close();
    communication_task_status_publisher_port.close();
    std::cout << "Calling close function in CommunicationsTaskThread\n";
    return;
  }

  void CommunicationsTaskThread::run()
  {
    input();
    update();
    output();
  }

  void CommunicationsTaskThread::afterStart( bool _success )
  {
  }

  void CommunicationsTaskThread::input()
  {
    qkey_press_event_   = key_press_event_subscriber_.bottle();
    qkey_release_event_ = key_release_event_subscriber_.bottle();

    if( qkey_press_event_.timestamp > qkey_release_event_.timestamp )
    {
      key_is_pressed_ = true;
    }
    else
    {
      key_is_pressed_ = false;
    }

    if( key_is_pressed_ )
    {
      if( 16777235 == qkey_press_event_.key || 111 == qkey_press_event_.native_scan_code )
      {
        up_    = true;
        down_  = false;
        right_ = false;
        left_  = false;
      }
      else if( 16777237 == qkey_press_event_.key || 116 == qkey_press_event_.native_scan_code )
      {
        up_    = false;
        down_  = true;
        right_ = false;
        left_  = false;
      }
      else if( 16777236 == qkey_press_event_.key || 114 == qkey_press_event_.native_scan_code )
      {
        up_    = false;
        down_  = false;
        right_ = true;
        left_  = false;
      }
      else if( 16777234 == qkey_press_event_.key || 113 == qkey_press_event_.native_scan_code )
      {
        up_    = false;
        down_  = false;
        right_ = false;
        left_  = true;
      }
      else
      {
        up_    = false;
        down_  = false;
        right_ = false;
        left_  = false;
      }
    }
    else
    {
      left_  = joystick_button_subscriber.left();
      right_ = joystick_button_subscriber.right();
      up_    = joystick_button_subscriber.up();
      down_  = joystick_button_subscriber.down();

    }
  }

  void CommunicationsTaskThread::output()
  {
    /* publisher */
    buffered_port.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( cv_image );
    buffered_port.write();

    if( need_instruction_ && is_started )
    {
      yarp::os::Bottle speech_bottle;
      yarp::os::Bottle response;
      speech_bottle.addString( "say" );
      speech_bottle.addString( instruction_comment_ );
      speech_client_port.prepare() = speech_bottle;
      speech_client_port.write();
      //     speech_client_port.write( speech_bottle, response );
      need_instruction_ = false;
      std::cout << "\033[33m" << "speak: say \"" << instruction_comment_ << "\"" << "\033[0m" << std::endl;
    }

    yarp::rosmsg::matb_msgs::Comm comm_task_message;
    comm_task_message.elapsed_time      = MatbEventServer::elapsed_time();
    comm_task_message.com1_integer_part = com1_integer_part_;
    comm_task_message.com1_decimal_part = com1_decimal_part_;
    comm_task_message.com2_integer_part = com2_integer_part_;
    comm_task_message.com2_decimal_part = com2_decimal_part_;
    comm_task_message.nav1_integer_part = nav1_integer_part_;
    comm_task_message.nav1_decimal_part = nav1_decimal_part_;
    comm_task_message.nav2_integer_part = nav2_integer_part_;
    comm_task_message.nav2_decimal_part = nav2_decimal_part_;

    comm_task_message.ref_com1_integer_part = ref_com1_integer_part_;
    comm_task_message.ref_com1_decimal_part = ref_com1_decimal_part_;
    comm_task_message.ref_com2_integer_part = ref_com2_integer_part_;
    comm_task_message.ref_com2_decimal_part = ref_com2_decimal_part_;
    comm_task_message.ref_nav1_integer_part = ref_nav1_integer_part_;
    comm_task_message.ref_nav1_decimal_part = ref_nav1_decimal_part_;
    comm_task_message.ref_nav2_integer_part = ref_nav2_integer_part_;
    comm_task_message.ref_nav2_decimal_part = ref_nav2_decimal_part_;


    if( com1_timer_.is_stopped() )
    {
      comm_task_message.com1_elapsed_time = 0;
    }
    else
    {
      comm_task_message.com1_elapsed_time = com1_timer_.elapsed().wall;
    }

    if( com2_timer_.is_stopped() )
    {
      comm_task_message.com2_elapsed_time = 0;
    }
    else
    {
      comm_task_message.com2_elapsed_time = com2_timer_.elapsed().wall;
    }

    if( nav1_timer_.is_stopped() )
    {
      comm_task_message.nav1_elapsed_time = 0;
    }
    else
    {
      comm_task_message.nav1_elapsed_time = nav1_timer_.elapsed().wall;
    }

    if( nav2_timer_.is_stopped() )
    {
      comm_task_message.nav2_elapsed_time = 0;
    }
    else
    {
      comm_task_message.nav2_elapsed_time = nav2_timer_.elapsed().wall;
    }

    communication_task_status_publisher_port.prepare() = comm_task_message;
    communication_task_status_publisher_port.write();

  }

};

