#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/PeriodicThread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <yarp/cv/Cv.h>
#include <matb/yarp_subscriber/yarp_subscriber/yarp_subscriber.hpp>
#include <matb/yarp_subscriber/joystick_button_subscriber/joystick_button_subscriber.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
#include <matb/algorithm/system_monitoring_task/system_monitoring_task.hpp>
#include <yarp/rosmsg/matb_msgs/QKey.h>
#include <yarp/rosmsg/matb_msgs/Sysmon.h>
namespace matb
{

  class SystemMonitoringTaskThread : public SystemMonitoringTask, public yarp::os::PeriodicThread
  {
    public:
      SystemMonitoringTaskThread( const double& _period, yarp::os::ResourceFinder& _rf );
      ~SystemMonitoringTaskThread();
      void threadRelease() override;
      void afterStart( bool _success ) override;
    protected:
      yarp::os::ResourceFinder rf_;
      void run() override;
      bool threadInit() override;
      void input();
      void output();

      /* subscriber */
      matb::YarpSubscriber <yarp::rosmsg::matb_msgs::QKey>   key_press_event_subscriber_;
      matb::JoystickButtonSubscriber                         joystick_button_subscriber;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_press_event_subscriber_port_;
      yarp::os::BufferedPort <yarp::os::Bottle>              joystick_button_subscriber_port;

      /* pubscriber */
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> image_buffered_port;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::Sysmon>           system_monitoring_task_publisher_port_;

  };
};




