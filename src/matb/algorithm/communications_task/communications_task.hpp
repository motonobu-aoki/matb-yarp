#pragma once

#include <iostream>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <matb/algorithm/matb_event_server/matb_event_server.hpp>

namespace matb
{
  class CommunicationsTask
  {
      enum class State : uint
      {
        NAV1, NAV2, COM1, COM2, NAV1_INTEGER, NAV2_INTEGER, COM1_INTEGER, COM2_INTEGER, NAV1_DECIMAL, NAV2_DECIMAL, COM1_DECIMAL, COM2_DECIMAL
      };

      enum class Language : uint
      {
        ENGLISH, ITALIAN
      };

    public:
      CommunicationsTask();
      ~CommunicationsTask();
      void start();
      void stop();

    protected:
      void update();
      cv::Mat cv_image;
      bool need_instruction_ = false;
      std::string instruction_comment_ = "";

      boost::timer::cpu_timer com1_timer_;
      boost::timer::cpu_timer com2_timer_;
      boost::timer::cpu_timer nav1_timer_;
      boost::timer::cpu_timer nav2_timer_;

      int ref_nav1_integer_part_ = 120;
      int ref_nav1_decimal_part_ = 000;
      int ref_nav2_integer_part_ = 120;
      int ref_nav2_decimal_part_ = 000;
      int ref_com1_integer_part_ = 120;
      int ref_com1_decimal_part_ = 000;
      int ref_com2_integer_part_ = 120;
      int ref_com2_decimal_part_ = 000;

      int nav1_integer_part_ = ref_nav1_integer_part_;
      int nav1_decimal_part_ = ref_nav1_decimal_part_;
      int nav2_integer_part_ = ref_nav2_integer_part_;
      int nav2_decimal_part_ = ref_nav2_decimal_part_;
      int com1_integer_part_ = ref_com1_integer_part_;
      int com1_decimal_part_ = ref_com1_decimal_part_;
      int com2_integer_part_ = ref_com2_integer_part_;
      int com2_decimal_part_ = ref_com2_decimal_part_;

      bool a_            = false;
      bool b_            = false;
      bool x_            = false;
      bool y_            = false;
      bool lb_           = false;
      bool rb_           = false;
      bool back_         = false;
      bool start_        = false;
      bool guide_        = false;
      bool left_stick_   = false;
      bool right_stick_  = false;
      bool left_         = false;
      bool right_        = false;
      bool up_           = false;
      bool down_         = false;
      bool is_started    = false;

    private:
      void updateState();
      void updateFrequency();
      void draw();
      void saveLastKeys();
      void updateMatbEvent();

      State current_state = State::NAV1;
      std::deque <std::shared_ptr< CommunicationEvent >> events_;

      /* values of picture */
      int pixel_size = 450;
      int line_thickness = 2;
      int text_thickness = 1;

      cv::Scalar line_color;
      cv::Scalar text_color;
      cv::Scalar liquid_color;
      cv::Scalar failed_color;
      cv::Scalar emphasized_text_color;
      cv::Scalar bar_color;
      cv::Scalar nav1_text_color;
      cv::Scalar nav1_integer_text_color;
      cv::Scalar nav1_decimal_text_color;
      cv::Scalar nav2_text_color;
      cv::Scalar nav2_integer_text_color;
      cv::Scalar nav2_decimal_text_color;
      cv::Scalar com1_text_color;
      cv::Scalar com1_integer_text_color;
      cv::Scalar com1_decimal_text_color;
      cv::Scalar com2_text_color;
      cv::Scalar com2_integer_text_color;
      cv::Scalar com2_decimal_text_color;

      int freq_max_ = 200;
      int freq_min_ = 100;

      bool a0_           = false;
      bool b0_           = false;
      bool x0_           = false;
      bool y0_           = false;
      bool lb0_          = false;
      bool rb0_          = false;
      bool back0_        = false;
      bool start0_       = false;
      bool guide0_       = false;
      bool left_stick0_  = false;
      bool right_stick0_ = false;
      bool left0_        = false;
      bool right0_       = false;
      bool up0_          = false;
      bool down0_        = false;


  };
};




