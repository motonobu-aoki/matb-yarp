#pragma once

/* yarp */
#include <yarp/os/Network.h>
#include <yarp/os/RFModule.h>
#include <yarp/os/BufferedPort.h>
#include <yarp/os/impl/TextCarrier.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/cv/Cv.h>

/* yarp bottle */

/* c++ */
#include <unistd.h>
#include <iostream>
#include <cstdio>
#include <thread>

/* boost */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

/* opencv */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

/* matb */
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
#include <matb/thread/communications_task_thread/communications_task_thread.hpp>
#include <matb/thread/resource_management_task_thread/resource_management_task_thread.hpp>
#include <matb/thread/scheduling_display_thread/scheduling_display_thread.hpp>
#include <matb/thread/system_monitoring_task_thread/system_monitoring_task_thread.hpp>
#include <matb/thread/tracking_task_thread/tracking_task_thread.hpp>
#include <yarp/rosmsg/matb_msgs/QKey.h>
#include <yarp/rosmsg/std_msgs/Bool.h>
#include <yarp/rosmsg/std_msgs/Time.h>
namespace matb
{
  class MatbModule : public yarp::os::RFModule
  {
    public:
      double getPeriod() override;
      bool updateModule() override;
      bool configure( yarp::os::ResourceFinder& _rf ) override;
      bool interruptModule() override;
      bool close() override;
      bool respond( const yarp::os::Bottle& command, yarp::os::Bottle& reply ) override;
      void input();
      void output();
    private:
      void clockStart();
      void checkClockStart();
      void eventStart();
      void eventStop();
      void updateMatbEvent();

      bool resman_    = false;
      bool sysmon_    = false;
      bool track_     = false;
      bool sched_     = false;
      bool comm_      = false;
      bool is_started = false;
      std::string condition_ = "nonsocial";
      
      double frequency_ = 30.0;
      double period_;

      /* thread */
      std::shared_ptr <CommunicationsTaskThread>             communications_task_thread;
      std::shared_ptr <ResourceManagementTaskThread>         resource_management_task_thread;
      std::shared_ptr <SchedulingDisplayThread>              scheduling_display_thread;
      std::shared_ptr <SystemMonitoringTaskThread>           system_monitoring_task_thread;
      std::shared_ptr <TrackingTaskThread>                   tracking_task_thread;
      /* subscriber */
      matb::YarpSubscriber <yarp::rosmsg::matb_msgs::QKey>   key_press_event_subscriber;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_press_event_subscriber_port;

      matb::YarpSubscriber< yarp::rosmsg::std_msgs::Time >   experiment_window_elapsed_time_subscriber_;
      yarp::os::BufferedPort <yarp::rosmsg::std_msgs::Time>  experiment_window_elapsed_time_subscriber_port_;

      std::deque <std::shared_ptr< SystemEvent >> events_;
      //     MATBEventServer matb_event_server;

      boost::property_tree::ptree p_tree;

      yarp::rosmsg::matb_msgs::QKey key_press_event_;

      std::string key_text_                 = "";
      int         native_virtual_key_       = -1;
      long int    last_key_press_time_stamp = 0;
  };
}

