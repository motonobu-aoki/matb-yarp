#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
namespace matb
{
  class SchedulingDisplay
  {
    public:
      SchedulingDisplay();
      ~SchedulingDisplay();
      void start();
      void stop();
    protected:
      void update();

      bool is_started     = false;

      cv::Mat cv_image;

      std::chrono::seconds control_start_time;
      std::chrono::seconds control_end_time;
      std::chrono::seconds resource_management_task_start_time;
      std::chrono::seconds resource_management_task_stop_time;
      std::chrono::seconds system_monitoring_task_start_time;
      std::chrono::seconds system_monitoring_task_stop_time;

      std::vector <std::pair< std::chrono::seconds, std::chrono::seconds >> manual_tracking_durations;
      std::vector <std::pair< std::chrono::seconds, std::chrono::seconds >> communication_task_durations;
      std::deque <std::shared_ptr< SchedulingEvent >> scheduling_events_;
      std::deque <std::shared_ptr< SystemEvent >>     system_events_;

    private:
      void takeInEachTaskStartAndEndTime();
      void draw();
      void drawElapsedTime();
      void drawSchedulingGraph();

      /* values of picture */
      int  line_thickness = 1;
      int  text_thickness = 1;
      int  pixel_size     = 450;
      int max_min_    = 10;
      int max_second_ = max_min_ * 60;

      cv::Scalar line_color;
      cv::Scalar text_color;
      cv::Scalar gage_color;
      cv::Scalar failed_color;
      cv::Scalar bar_color;

  };

};

