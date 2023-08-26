#pragma once

#include <iostream>
#include <stdio.h>
#include <yarp/conf/system.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/os/PeriodicThread.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <yarp/cv/Cv.h>
#include <matb/yarp_subscriber/yarp_subscriber/yarp_subscriber.hpp>
#include <matb/yarp_subscriber/joystick_button_subscriber/joystick_button_subscriber.hpp>
#include <matb/algorithm/communications_task/communications_task.hpp>
#include <yarp/rosmsg/matb_msgs/Comm.h>
#include <yarp/rosmsg/matb_msgs/QKey.h>

namespace matb
{

  class CommunicationsTaskThread : public CommunicationsTask, public yarp::os::PeriodicThread
  {
    public:
      CommunicationsTaskThread( double _period, yarp::os::ResourceFinder& _rf );
      ~CommunicationsTaskThread();
      void input();
      void output();
      void threadRelease() override;
    protected:
      void afterStart( bool _success ) override;
      bool threadInit() override;
      void run() override;

      bool                          key_is_pressed_ = false;

      yarp::os::ResourceFinder rf_;

      yarp::rosmsg::matb_msgs::QKey qkey_press_event_;
      yarp::rosmsg::matb_msgs::QKey qkey_release_event_;

      matb::JoystickButtonSubscriber                         joystick_button_subscriber;
      yarp::os::BufferedPort <yarp::os::Bottle>              joystick_button_subscriber_port;
      matb::YarpSubscriber <yarp::rosmsg::matb_msgs::QKey>   key_press_event_subscriber_;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_press_event_subscriber_port_;
      matb::YarpSubscriber <yarp::rosmsg::matb_msgs::QKey>   key_release_event_subscriber_;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_release_event_subscriber_port_;

      /* publisher */
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> buffered_port;
      yarp::os::BufferedPort <yarp::os::Bottle>                          speech_client_port;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::Comm>             communication_task_status_publisher_port;

  };

};
