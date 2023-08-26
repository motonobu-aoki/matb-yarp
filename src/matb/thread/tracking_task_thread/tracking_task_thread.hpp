#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/cv/Cv.h>
#include <matb/yarp_subscriber/yarp_subscriber/yarp_subscriber.hpp>
#include <matb/yarp_subscriber/joystick_axis_subscriber/joystick_axis_subscriber.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
#include <yarp/rosmsg/matb_msgs/Point2D.h>
#include <yarp/rosmsg/matb_msgs/Tracking.h>
#include <matb/algorithm/tracking_task/tracking_task.hpp>
namespace matb
{
  class TrackingTaskThread : public TrackingTask, public yarp::os::PeriodicThread
  {
    public:
      TrackingTaskThread( const double& _period, yarp::os::ResourceFinder& _rf );
      ~TrackingTaskThread();

      void threadRelease() override;
      void afterStart( bool _success ) override;
    protected:
      yarp::os::ResourceFinder rf_;
      void run() override;
      bool threadInit() override;
      void input();
      void output();

      /* subscriber */
      matb::JoystickAxisSubscriber              joystick_axis_subscriber;
      yarp::os::BufferedPort <yarp::os::Bottle> joystick_axis_subscriber_port;

      /* publisher */
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> image_publisher_port;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::Tracking>         tracking_task_status_publisher_port;

      yarp::sig::ImageOf <yarp::sig::PixelRgb> yarp_image;
  };
};


