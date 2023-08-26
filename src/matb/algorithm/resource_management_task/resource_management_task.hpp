#pragma once

#include <iostream>
#include <cstdio>
#include <boost/timer/timer.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>
namespace matb
{
  class ResourceManagementTask
  {
    public:
      ResourceManagementTask();
      ~ResourceManagementTask();
    public:
      void start();
      void stop();
      //     void input();
      //     void output();
      void frequency( const double& _frequency );

      /* needed to update the key value in inherited class */

      long int last_key_press_time_stamp = 0;
      int      native_virtual_key_       = 0;

      /* -------------------------------------------------- */
    protected:
      bool is_started        = false;
      bool valve_1_is_on     = true;
      bool valve_2_is_on     = true;
      bool valve_3_is_on     = true;
      bool valve_4_is_on     = true;
      bool valve_5_is_on     = true;
      bool valve_6_is_on     = true;
      bool valve_7_is_on     = true;
      bool valve_8_is_on     = true;
      bool valve_1_is_failed = false;
      bool valve_2_is_failed = false;
      bool valve_3_is_failed = false;
      bool valve_4_is_failed = false;
      bool valve_5_is_failed = false;
      bool valve_6_is_failed = false;
      bool valve_7_is_failed = false;
      bool valve_8_is_failed = false;

      cv::Mat    resman_cv_image_;
      cv::Mat    pump_status_cv_image_;

      std::deque <std::shared_ptr< ResourceManagementEvent >> events_;

      boost::timer::cpu_timer tank_A_timer_;
      boost::timer::cpu_timer tank_B_timer_;

      /* values of the resource management task*/
      const double max_amount_of_tank_A     = 4000;
      double       amount_of_tank_A         = 2500;
      double       proportion_of_tank_A     = 0;
      const double max_amount_of_tank_B     = 4000;
      double       amount_of_tank_B         = 2500;
      double       proportion_of_tank_B     = 0;
      const double max_amount_of_tank_C     = 2000;
      double       amount_of_tank_C         = 1000;
      double       proportion_of_tank_C     = 0;
      const double max_amount_of_tank_D     = 2000;
      double       amount_of_tank_D         = 1000;
      double       proportion_of_tank_D     = 0;
      const double proportion_of_tank_E     = 1.0;
      const double proportion_of_tank_F     = 1.0;

      double       initial_pump_flow_rate_1 = 800; /* [/min]*/
      double       initial_pump_flow_rate_2 = 600; /* [/min]*/
      double       initial_pump_flow_rate_3 = 800; /* [/min]*/
      double       initial_pump_flow_rate_4 = 600; /* [/min]*/
      double       initial_pump_flow_rate_5 = 600; /* [/min]*/
      double       initial_pump_flow_rate_6 = 600; /* [/min]*/
      double       initial_pump_flow_rate_7 = 400; /* [/min]*/
      double       initial_pump_flow_rate_8 = 400; /* [/min]*/
      double       initial_pump_flow_rate_A = 800; /* [/min]*/
      double       initial_pump_flow_rate_B = 800; /* [/min]*/

      double pump_flow_rate_1 = initial_pump_flow_rate_1; /* [/min]*/
      double pump_flow_rate_2 = initial_pump_flow_rate_2; /* [/min]*/
      double pump_flow_rate_3 = initial_pump_flow_rate_3; /* [/min]*/
      double pump_flow_rate_4 = initial_pump_flow_rate_4; /* [/min]*/
      double pump_flow_rate_5 = initial_pump_flow_rate_5; /* [/min]*/
      double pump_flow_rate_6 = initial_pump_flow_rate_6; /* [/min]*/
      double pump_flow_rate_7 = initial_pump_flow_rate_7; /* [/min]*/
      double pump_flow_rate_8 = initial_pump_flow_rate_8; /* [/min]*/
      double pump_flow_rate_A = initial_pump_flow_rate_A; /* [/min]*/
      double pump_flow_rate_B = initial_pump_flow_rate_B; /* [/min]*/

    protected:
      void update();
      void drawChainLine( cv::Mat img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, int thickness, int lineType, int shift = 0 );
    private:
      double frequency_ = 0.03333333333;
      void updateMatbEvent();
      void updateValves();
      void updateAmountOfEachTank();
      void updateProportionOfEachTank();
      void draw();
      void drawPumpStatusImage();
      void drawResourceManagementTaskImage();

      /* values of picture */
      int pixel_size     = 450;
      int line_thickness = 2;
      int text_thickness = 1;

      cv::Scalar line_color;
      cv::Scalar text_color;
      cv::Scalar liquid_color;
      cv::Scalar failed_color;
      cv::Scalar unfailed_color;
      cv::Scalar bar_color;
  };

};
