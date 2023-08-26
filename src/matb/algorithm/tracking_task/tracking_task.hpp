#pragma once

#include <iostream>
#include <cstdio>
#include <cmath>
#include <random>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/timer/timer.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
namespace matb
{
  class TrackingTask
  {
      enum class LowMediumHigh : uint
      {
        LOW, MEDIUM, HIGH
      };

    public:
      TrackingTask();
      ~TrackingTask();

      void start();
      void stop();
    protected:
      void update();

      double frequency_  = 0.0333333333;
      double joystick_x_ = 0;
      double joystick_y_ = 0;
      bool considered_dynamics_ = false;

      /* x direction */
      double x1 = 0;/* position */
      double v1 = 0;/* velocity */
      double a1 = 0;/* acceleration */
      /* y direction */
      double y1 = 0;/* position */
      double w1 = 0;/* velocity */
      double b1 = 0;/* acceleration */

      boost::timer::cpu_timer out_of_track_timer;

      bool is_manual_mode = false;
      bool is_started     = false;

      cv::Mat cv_image;
      std::deque <std::shared_ptr< SchedulingEvent >> scheduling_events_;

    private:
      void draw();
      void drawGrid();
      void drawTarget();
      void drawText();
      void drawChainLine( cv::Mat img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, int thickness = 1, int lineType = cv::LINE_8, int shift = 0 );
      void updateTargetValue();
      void updateMatbEvents();

      /* values of target's dynamics */
      std::random_device              random_device;
      std::mt19937                    mt19937;
      std::uniform_int_distribution<> uniform_int_distribution;
      std::normal_distribution<>      normal_distribution;

      //   double       standard_deviation = 0.015;
      double       standard_deviation = 0.008;
      //   double standard_deviation = 1.0;
      const double unit_norm          = 1.0;
      //   double       joystick_gain      = 0.02;
      double       joystick_gain      = 0.01;
      double       gravity            = 0.0;
      const double v_max              = 2;
      const double a_max              = 1;
      double viscocity        = 1.0;

      cv::Scalar line_color;
      cv::Scalar text_color;
      cv::Scalar arrow_color;
      cv::Scalar pole_color;
      cv::Point  cv_target_point;
      int    target_thickness = 3;

      /* values of picture */
      int  pixel_size       = 450;
      uint radius_of_target = pixel_size * 3 / 40;

      LowMediumHigh update_value   = LowMediumHigh::MEDIUM;
      LowMediumHigh response_value = LowMediumHigh::MEDIUM;

      /* x direction */
      double x0 = 0;/* position */
      double v0 = 0;/* velocity */
      double a0 = 0;/* acceleration */
      /* y direction */
      double y0 = 0;/* position */
      double w0 = 0;/* velocity */
      double b0 = 0;/* acceleration */


  };
};
