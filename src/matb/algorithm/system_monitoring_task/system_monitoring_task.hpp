#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <boost/timer/timer.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
namespace matb
{
  class SystemMonitoringTask
  {
    public:
      SystemMonitoringTask();
      ~SystemMonitoringTask();
      void start();
      void stop();
    protected:
      void update();

      cv::Mat cv_image;

      int  native_virtual_key_ = -1;
      bool is_started          = false;

      long int last_key_press_time_stamp = 0;

      bool button_a_       = false;
      bool button_b_       = false;
      bool button_x_       = false;
      bool button_y_       = false;
      bool button_lb_      = false;
      bool button_rb_      = false;

      bool event_f1_is_on_ = false;
      bool event_f2_is_on_ = false;
      bool event_f3_is_on_ = false;
      bool event_f4_is_on_ = false;
      bool event_f5_is_on_ = false;
      bool event_f6_is_on_ = false;

      boost::timer::cpu_timer f1_timer_;
      boost::timer::cpu_timer f2_timer_;
      boost::timer::cpu_timer f3_timer_;
      boost::timer::cpu_timer f4_timer_;
      boost::timer::cpu_timer f5_timer_;
      boost::timer::cpu_timer f6_timer_;

      long int elapsed_time_f1_ = 0; /* millisecond */
      long int elapsed_time_f2_ = 0; /* millisecond */
      long int elapsed_time_f3_ = 0; /* millisecond */
      long int elapsed_time_f4_ = 0; /* millisecond */
      long int elapsed_time_f5_ = 0; /* millisecond */
      long int elapsed_time_f6_ = 0; /* millisecond */

      /* task state */
      int base_position_f1_ = 0;
      int position_f1_      = 0;
      int base_position_f2_ = 0;
      int position_f2_      = 0;
      int base_position_f3_ = 0;
      int position_f3_      = 0;
      int base_position_f4_ = 0;
      int position_f4_      = 0;

      bool is_green_ = true;
      bool is_red_   = false;

      std::deque <std::shared_ptr< SystemMonitoringEvent >> system_monitoring_events_;

      std::chrono::time_point <std::chrono::steady_clock> time_point_f1_;
      std::chrono::time_point <std::chrono::steady_clock> time_point_f2_;
      std::chrono::time_point <std::chrono::steady_clock> time_point_f3_;
      std::chrono::time_point <std::chrono::steady_clock> time_point_f4_;
      std::chrono::time_point <std::chrono::steady_clock> time_point_f5_;
      std::chrono::time_point <std::chrono::steady_clock> time_point_f6_;

    private:
      void updateMatbEvent();
      void draw();

      int  line_thickness  = 2;
      int  text_thickness  = 1;

      /* values of picture */
      int     pixel_size = 450;
      std::random_device              random_device;
      std::mt19937                    mt19937;
      std::uniform_int_distribution<> uniform_int_distribution;
      std::normal_distribution<>      normal_distribution;
      uint update_counter_ = 0;
      cv::Scalar line_color;
      cv::Scalar text_color;
      cv::Scalar sky_blue;
      cv::Scalar dark_blue;

  };

};


