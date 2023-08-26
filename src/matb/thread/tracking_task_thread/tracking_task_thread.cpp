#include "tracking_task_thread.hpp"
namespace matb
{
  TrackingTaskThread::TrackingTaskThread( const double& _period, yarp::os::ResourceFinder& _rf ) : PeriodicThread( _period )
  {
    rf_ = _rf;
  }
  TrackingTaskThread::~TrackingTaskThread()
  {
  }

  bool TrackingTaskThread::threadInit()
  {
    /* subscriber */
    joystick_axis_subscriber_port.useCallback( joystick_axis_subscriber );
    joystick_axis_subscriber_port.setReplier( joystick_axis_subscriber );
    joystick_axis_subscriber_port.open( "/" + rf_.find( "name" ).asString() + "/tracking_task/joystick_axis/sub" );

    /* publisher */
    image_publisher_port.open( "/" + rf_.find( "name" ).asString() + "/tracking_task/image/pub" );
    tracking_task_status_publisher_port.open( "/" + rf_.find( "name" ).asString() + "/tracking_task/tracking_status/pub" );

    return true;
  }

  void TrackingTaskThread::threadRelease()
  {
    /* subscriber */
    joystick_axis_subscriber_port.close();
    /* publisher */
    image_publisher_port.close();
    tracking_task_status_publisher_port.close();
    std::cout << "Calling close function in TrackingTaskThread\n";
    return;
  }

  void TrackingTaskThread::afterStart( bool _success )
  {
  }

  void TrackingTaskThread::input()
  {
    //   joystick_x_ = joystick_axis_subscriber.lx();
    //   joystick_y_ = joystick_axis_subscriber.ly();

    if( std::abs( joystick_axis_subscriber.lx() ) < std::abs( joystick_axis_subscriber.rx() ) )
    {
      joystick_x_ = joystick_axis_subscriber.rx();
    }
    else
    {
      joystick_x_ = joystick_axis_subscriber.lx();
    }

    if( std::abs( joystick_axis_subscriber.ly() ) < std::abs( joystick_axis_subscriber.ry() ) )
    {
      joystick_y_ = joystick_axis_subscriber.ry();
    }
    else
    {
      joystick_y_ = joystick_axis_subscriber.ly();
    }
  }

  void TrackingTaskThread::output()
  {
    /* publisher */
    image_publisher_port.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( cv_image );
    image_publisher_port.write();
    yarp::rosmsg::matb_msgs::Tracking tracking_task_message;
    tracking_task_message.elapsed_time = MatbEventServer::elapsed_time();
    tracking_task_message.point.x      = x1;
    tracking_task_message.point.y      = y1;

    if( out_of_track_timer.is_stopped() )
    {
      tracking_task_message.out_of_track_elapsed_time = 0;
    }
    else
    {
      tracking_task_message.out_of_track_elapsed_time = out_of_track_timer.elapsed().wall;
    }

    tracking_task_status_publisher_port.prepare() = tracking_task_message;
    tracking_task_status_publisher_port.write();
  }

  void TrackingTaskThread::run()
  {
    input();
    update();
    output();
  }

};
