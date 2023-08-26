#pragma once

#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/PeriodicThread.h>
#include <yarp/cv/Cv.h>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
#include <matb/algorithm/resource_management_task/resource_management_task.hpp>
#include <matb/yarp_subscriber/yarp_subscriber/yarp_subscriber.hpp>
#include <yarp/rosmsg/matb_msgs/QKey.h>
#include <yarp/rosmsg/matb_msgs/Resman.h>
namespace matb
{

  class ResourceManagementTaskThread : public ResourceManagementTask, public yarp::os::PeriodicThread
  {
    public:
      ResourceManagementTaskThread( const double& _period, yarp::os::ResourceFinder& _rf );
      ~ResourceManagementTaskThread();
      void threadRelease() override;
      void afterStart( bool _success ) override;
    protected:
      void run() override;
      bool threadInit() override;
      void input();
      void output();

      yarp::os::ResourceFinder rf_;
      /* subscriber */
      matb::YarpSubscriber <yarp::rosmsg::matb_msgs::QKey>   key_press_event_subscriber_;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_press_event_subscriber_port_;

      /* publisher */
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> resman_image_publisher_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> pump_status_image_buffered_port_;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::Resman>           resman_status_publisher_port_;
  };

};

