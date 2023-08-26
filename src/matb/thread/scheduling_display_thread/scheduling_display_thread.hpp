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
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
#include <matb/algorithm/scheduling_display/scheduling_display.hpp>

namespace matb
{
  class SchedulingDisplayThread : public SchedulingDisplay, public yarp::os::PeriodicThread
  {
    public:
      SchedulingDisplayThread( const double& _period, yarp::os::ResourceFinder& _rf );
      ~SchedulingDisplayThread();
      void threadRelease() override;
      void afterStart( bool _success ) override;
    protected:
      yarp::os::ResourceFinder rf_;
      bool threadInit() override;
      void run() override;
      void input();
      void output();
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> buffered_port;
  };

};


