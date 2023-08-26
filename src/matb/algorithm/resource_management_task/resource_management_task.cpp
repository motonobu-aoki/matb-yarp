#include "resource_management_task.hpp"
namespace matb
{
  ResourceManagementTask::ResourceManagementTask()
  {
    tank_A_timer_.stop();
    tank_B_timer_.stop();
    events_        = MatbEventServer::resource_management_events();
    line_color     = cv::Scalar( 50, 70, 70 );
    text_color     = cv::Scalar( 150, 50, 0 );
    liquid_color   = cv::Scalar( 200, 180, 250 );
    unfailed_color = cv::Scalar( 0, 255, 0 );
    failed_color   = cv::Scalar( 0, 0, 255 );
    bar_color      = cv::Scalar( 255, 150, 150 );
  }

  ResourceManagementTask::~ResourceManagementTask()
  {
  }

  void ResourceManagementTask::frequency( const double& _frequency )
  {
    frequency_ = _frequency;
  }

  void ResourceManagementTask::start()
  {
    is_started = true;
  }

  void ResourceManagementTask::stop()
  {
    is_started = false;
  }

  void ResourceManagementTask::update()
  {
    if( is_started )
    {
      updateMatbEvent();
      updateValves();
      updateAmountOfEachTank();
    }

    updateProportionOfEachTank();
    draw();
  }

  void ResourceManagementTask::draw()
  {
    drawPumpStatusImage();
    drawResourceManagementTaskImage();
  }

  void ResourceManagementTask::drawPumpStatusImage()
  {
    pump_status_cv_image_ = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );
    putText( pump_status_cv_image_, "1", cv::Point( pixel_size * 3 / 10, pixel_size * 2 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "2", cv::Point( pixel_size * 3 / 10, pixel_size * 3 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "3", cv::Point( pixel_size * 3 / 10, pixel_size * 4 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "4", cv::Point( pixel_size * 3 / 10, pixel_size * 5 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "5", cv::Point( pixel_size * 3 / 10, pixel_size * 6 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "6", cv::Point( pixel_size * 3 / 10, pixel_size * 7 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "7", cv::Point( pixel_size * 3 / 10, pixel_size * 8 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "8", cv::Point( pixel_size * 3 / 10, pixel_size * 9 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "FLOW", cv::Point( pixel_size * 3 / 10, pixel_size * 1 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, "RATES", cv::Point( pixel_size * 6 / 10, pixel_size * 1 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_1 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 2 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 1.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 2.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_2 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 3 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 2.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 3.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_3 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 4 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 3.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 4.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_4 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 5 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 4.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 5.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_5 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 6 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 5.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 6.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_6 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 7 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 6.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 7.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_7 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 8 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 7.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 8.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
    putText( pump_status_cv_image_, std::to_string( int( pump_flow_rate_8 ) ), cv::Point( pixel_size * 6 / 10, pixel_size * 9 / 10 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::rectangle( pump_status_cv_image_, cv::Point( pixel_size * 5.8 / 10, pixel_size * 8.5 / 10 ), cv::Point( pixel_size * 7.5 / 10, pixel_size * 9.2 / 10 ), line_color, line_thickness, cv::LINE_8 );
  }

  void ResourceManagementTask::drawResourceManagementTaskImage()
  {
    resman_cv_image_ = cv::Mat( pixel_size, pixel_size, CV_8UC3, cv::Scalar( 255, 255, 255 ) );
    /* A */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 3 / 20, pixel_size * ( 10 - ( 10 - 6 ) * proportion_of_tank_A ) / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 10 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* left bar */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 2.5 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 8 / 20 ), bar_color, -1, cv::LINE_8 );
    /* right bar */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 7.5 / 20, pixel_size * 8 / 20 ), bar_color, -1, cv::LINE_8 );
    /* border line*/
    drawChainLine( resman_cv_image_, cv::Point( pixel_size * 3 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 7 / 20 ), bar_color, 1, cv::LINE_8 );
    drawChainLine( resman_cv_image_, cv::Point( pixel_size * 3 / 20, pixel_size * 8 / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 8 / 20 ), bar_color, 1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 3 / 20, pixel_size * 6 / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 10 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 2.5 / 20, pixel_size * 7.5 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 7.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 7.5 / 20 ), cv::Point( pixel_size * 7.5 / 20, pixel_size * 7.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "A", cv::Point( pixel_size * 2 / 20, pixel_size * 6 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    if( amount_of_tank_A < 2000 || 3000 < amount_of_tank_A )
    {
      putText( resman_cv_image_, std::to_string( int( amount_of_tank_A ) ), cv::Point( pixel_size * 4 / 20, pixel_size * 11 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, failed_color, text_thickness, cv::LINE_AA );
    }
    else
    {
      putText( resman_cv_image_, std::to_string( int( amount_of_tank_A ) ), cv::Point( pixel_size * 4 / 20, pixel_size * 11 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    }

    /* B */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 13 / 20, pixel_size * ( 10 - ( 10 - 6 ) * proportion_of_tank_B ) / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 10 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* left bar */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 12.5 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 8 / 20 ), bar_color, -1, cv::LINE_8 );
    /* right bar */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 17.5 / 20, pixel_size * 8 / 20 ), bar_color, -1, cv::LINE_8 );
    /* border line*/
    drawChainLine( resman_cv_image_, cv::Point( pixel_size * 13 / 20, pixel_size * 7 / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 7 / 20 ), bar_color, 1, cv::LINE_8 );
    drawChainLine( resman_cv_image_, cv::Point( pixel_size * 13 / 20, pixel_size * 8 / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 8 / 20 ), bar_color, 1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 13 / 20, pixel_size * 6 / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 10 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 12.5 / 20, pixel_size * 7.5 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 7.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 7.5 / 20 ), cv::Point( pixel_size * 17.5 / 20, pixel_size * 7.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "B", cv::Point( pixel_size * 12 / 20, pixel_size * 6 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );

    if( amount_of_tank_B < 2000 || 3000 < amount_of_tank_B )
    {
      putText( resman_cv_image_, std::to_string( int( amount_of_tank_B ) ), cv::Point( pixel_size * 14 / 20, pixel_size * 11 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, failed_color, text_thickness, cv::LINE_AA );
    }
    else
    {
      putText( resman_cv_image_, std::to_string( int( amount_of_tank_B ) ), cv::Point( pixel_size * 14 / 20, pixel_size * 11 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    }

    /* C */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 1 / 20, pixel_size * ( 18 - ( 18 - 14 ) * proportion_of_tank_C ) / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 18 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 1 / 20, pixel_size * 14 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 18 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "C", cv::Point( pixel_size * 0 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( resman_cv_image_, std::to_string( int( amount_of_tank_C ) ), cv::Point( pixel_size * 1 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    /* D */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * ( 18 - ( 18 - 14 ) * proportion_of_tank_D ) / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 18 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 14 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 18 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "D", cv::Point( pixel_size * 10 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( resman_cv_image_, std::to_string( int( amount_of_tank_D ) ), cv::Point( pixel_size * 11 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    /* E */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * ( 18 - ( 18 - 14 ) * proportion_of_tank_E ) / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 18 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 14 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 18 / 20 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( resman_cv_image_, "E", cv::Point( pixel_size * 6 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( resman_cv_image_, "Infinity", cv::Point( pixel_size * 7 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 900, text_color, text_thickness, cv::LINE_AA );
    /* F */
    /* liquid */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * ( 18 - ( 18 - 14 ) * proportion_of_tank_F ) / 20 ), cv::Point( pixel_size * 19 / 20, pixel_size * 18 / 20 ), liquid_color, -1, cv::LINE_8 );
    /* tank */
    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 14 / 20 ), cv::Point( pixel_size * 19 / 20, pixel_size * 18 / 20 ), line_color, line_thickness * 2, cv::LINE_8 );
    putText( resman_cv_image_, "F", cv::Point( pixel_size * 16 / 20, pixel_size * 14 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    putText( resman_cv_image_, "Infinity", cv::Point( pixel_size * 17 / 20, pixel_size * 19 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 900, text_color, text_thickness, cv::LINE_AA );

    /* A->B */
    /* valve 7 */
    if( valve_7_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 6 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 7 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_7_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 6 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 7 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 6 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 7 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, " 7>", cv::Point( pixel_size * 9.2 / 20, pixel_size * 6.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 6.5 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 6.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 6.5 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 6.5 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* B->A */
    /* valve 8 */
    if( valve_8_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 8 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 9 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_8_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 8 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 9 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 9 / 20, pixel_size * 8 / 20 ), cv::Point( pixel_size * 11 / 20, pixel_size * 9 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "<8", cv::Point( pixel_size * 9.2 / 20, pixel_size * 8.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 8.5 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 8.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 8.5 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 8.5 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* C->A */
    /* valve 1 */
    if( valve_1_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 1 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 12 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_1_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 1 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 12 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 1 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 12 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "^1", cv::Point( pixel_size * 1.2 / 20, pixel_size * 11.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 2 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 3 / 20, pixel_size * 9 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 2 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 2 / 20, pixel_size * 11 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 2 / 20, pixel_size * 12 / 20 ), cv::Point( pixel_size * 2 / 20, pixel_size * 14 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* E->A */
    /* valve 2 */
    if( valve_2_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 12 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_2_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 12 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 7 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 9 / 20, pixel_size * 12 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "^2", cv::Point( pixel_size * 7.2 / 20, pixel_size * 11.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 8 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 9 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 8 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 8 / 20, pixel_size * 11 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 8 / 20, pixel_size * 12 / 20 ), cv::Point( pixel_size * 8 / 20, pixel_size * 14 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* D->B */
    /* valve 5 */
    if( valve_5_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 4 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 6 / 20, pixel_size * 16.5 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_5_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 4 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 6 / 20, pixel_size * 16.5 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 4 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 6 / 20, pixel_size * 16.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "<5", cv::Point( pixel_size * 4.2 / 20, pixel_size * 16.3 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 3 / 20, pixel_size * 16 / 20 ), cv::Point( pixel_size * 4 / 20, pixel_size * 16 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 6 / 20, pixel_size * 16 / 20 ), cv::Point( pixel_size * 7 / 20, pixel_size * 16 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* E->B */
    /* valve 3 */
    if( valve_3_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 12 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_3_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 12 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 11 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 12 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "^3", cv::Point( pixel_size * 11.2 / 20, pixel_size * 11.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 12 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 13 / 20, pixel_size * 9 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 12 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 12 / 20, pixel_size * 11 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 12 / 20, pixel_size * 12 / 20 ), cv::Point( pixel_size * 12 / 20, pixel_size * 14 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* F->B */
    /* valve 4 */

    if( valve_4_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 19 / 20, pixel_size * 12 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_4_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 19 / 20, pixel_size * 12 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 17 / 20, pixel_size * 11 / 20 ), cv::Point( pixel_size * 19 / 20, pixel_size * 12 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "^4", cv::Point( pixel_size * 17.2 / 20, pixel_size * 11.8 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 18 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 9 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 18 / 20, pixel_size * 9 / 20 ), cv::Point( pixel_size * 18 / 20, pixel_size * 11 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 18 / 20, pixel_size * 12 / 20 ), cv::Point( pixel_size * 18 / 20, pixel_size * 14 / 20 ), line_color, line_thickness, cv::LINE_8 );

    /* F->E */
    /* valve 6 */
    if( valve_6_is_on )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 14 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 16 / 20, pixel_size * 16.5 / 20 ), unfailed_color, -1, cv::LINE_8 );
    }

    if( valve_6_is_failed )
    {
      cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 14 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 16 / 20, pixel_size * 16.5 / 20 ), failed_color, -1, cv::LINE_8 );
    }

    cv::rectangle( resman_cv_image_, cv::Point( pixel_size * 14 / 20, pixel_size * 15.5 / 20 ), cv::Point( pixel_size * 16 / 20, pixel_size * 16.5 / 20 ), line_color, line_thickness, cv::LINE_8 );
    putText( resman_cv_image_, "<6", cv::Point( pixel_size * 14.2 / 20, pixel_size * 16.3 / 20 ), cv::FONT_HERSHEY_COMPLEX, double( pixel_size ) / 700, text_color, text_thickness, cv::LINE_AA );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 13 / 20, pixel_size * 16 / 20 ), cv::Point( pixel_size * 14 / 20, pixel_size * 16 / 20 ), line_color, line_thickness, cv::LINE_8 );
    cv::line( resman_cv_image_, cv::Point( pixel_size * 16 / 20, pixel_size * 16 / 20 ), cv::Point( pixel_size * 17 / 20, pixel_size * 16 / 20 ), line_color, line_thickness, cv::LINE_8 );
  }

  void ResourceManagementTask::updateProportionOfEachTank()
  {
    proportion_of_tank_A = double( amount_of_tank_A ) / max_amount_of_tank_A;
    proportion_of_tank_B = double( amount_of_tank_B ) / max_amount_of_tank_B;
    proportion_of_tank_C = double( amount_of_tank_C ) / max_amount_of_tank_C;
    proportion_of_tank_D = double( amount_of_tank_D ) / max_amount_of_tank_D;
  }

  void ResourceManagementTask::updateValves()
  {
    switch( native_virtual_key_ )
    {
      case 49:
        valve_1_is_on = !valve_1_is_on;
        break;

      case 50:
        valve_2_is_on = !valve_2_is_on;
        break;

      case 51:
        valve_3_is_on = !valve_3_is_on;
        break;

      case 52:
        valve_4_is_on = !valve_4_is_on;
        break;

      case 53:
        valve_5_is_on = !valve_5_is_on;
        break;

      case 54:
        valve_6_is_on = !valve_6_is_on;
        break;

      case 55:
        valve_7_is_on = !valve_7_is_on;
        break;

      case 56:
        valve_8_is_on = !valve_8_is_on;
        break;

      default:
        break;
    }

    if( valve_1_is_failed )
    {
      valve_1_is_on = false;
    }

    if( valve_2_is_failed )
    {
      valve_2_is_on = false;
    }

    if( valve_3_is_failed )
    {
      valve_3_is_on = false;
    }

    if( valve_4_is_failed )
    {
      valve_4_is_on = false;
    }

    if( valve_5_is_failed )
    {
      valve_5_is_on = false;
    }

    if( valve_6_is_failed )
    {
      valve_6_is_on = false;
    }

    if( valve_7_is_failed )
    {
      valve_7_is_on = false;
    }

    if( valve_8_is_failed )
    {
      valve_8_is_on = false;
    }

    if( valve_1_is_on )
    {
      pump_flow_rate_1 = initial_pump_flow_rate_1;
    }
    else
    {
      pump_flow_rate_1 = 0;
    }

    if( valve_2_is_on )
    {
      pump_flow_rate_2 = initial_pump_flow_rate_2;
    }
    else
    {
      pump_flow_rate_2 = 0;
    }

    if( valve_3_is_on )
    {
      pump_flow_rate_3 = initial_pump_flow_rate_3;
    }
    else
    {
      pump_flow_rate_3 = 0;
    }

    if( valve_4_is_on )
    {
      pump_flow_rate_4 = initial_pump_flow_rate_4;
    }
    else
    {
      pump_flow_rate_4 = 0;
    }

    if( valve_5_is_on )
    {
      pump_flow_rate_5 = initial_pump_flow_rate_5;
    }
    else
    {
      pump_flow_rate_5 = 0;
    }

    if( valve_6_is_on )
    {
      pump_flow_rate_6 = initial_pump_flow_rate_6;
    }
    else
    {
      pump_flow_rate_6 = 0;
    }

    if( valve_7_is_on )
    {
      pump_flow_rate_7 = initial_pump_flow_rate_7;
    }
    else
    {
      pump_flow_rate_7 = 0;
    }

    if( valve_8_is_on )
    {
      pump_flow_rate_8 = initial_pump_flow_rate_8;
    }
    else
    {
      pump_flow_rate_8 = 0;
    }

    //   keyboard_subscriber.clearValue();
  }

  void ResourceManagementTask::updateAmountOfEachTank()
  {
    if( amount_of_tank_A > 3000 || amount_of_tank_A < 2000 )
    {
      if( tank_A_timer_.is_stopped() )
      {
        tank_A_timer_.start();
      }
    }
    else
    {
      tank_A_timer_.stop();
    }

    if( amount_of_tank_B > 3000 || amount_of_tank_B < 2000 )
    {
      if( tank_B_timer_.is_stopped() )
      {
        tank_B_timer_.start();
      }
    }
    else
    {
      tank_B_timer_.stop();
    }

    /* check full or empty */

    if( 0 >= int( amount_of_tank_A ) )
    {
      pump_flow_rate_7 = 0;
    }

    if( 0 >= int( amount_of_tank_B ) )
    {
      pump_flow_rate_8 = 0;
    }

    if( 0 >= int( amount_of_tank_C ) )
    {
      pump_flow_rate_1 = 0;
    }

    if( 0 >= int( amount_of_tank_D ) )
    {
      pump_flow_rate_3 = 0;
    }

    amount_of_tank_A = amount_of_tank_A + pump_flow_rate_1 / 60 * frequency_;
    amount_of_tank_A = amount_of_tank_A + pump_flow_rate_2 / 60 * frequency_;
    amount_of_tank_A = amount_of_tank_A - pump_flow_rate_7 / 60 * frequency_;
    amount_of_tank_A = amount_of_tank_A + pump_flow_rate_8 / 60 * frequency_;
    amount_of_tank_A = amount_of_tank_A - pump_flow_rate_A / 60 * frequency_;
    amount_of_tank_B = amount_of_tank_B + pump_flow_rate_3 / 60 * frequency_;
    amount_of_tank_B = amount_of_tank_B + pump_flow_rate_4 / 60 * frequency_;
    amount_of_tank_B = amount_of_tank_B + pump_flow_rate_7 / 60 * frequency_;
    amount_of_tank_B = amount_of_tank_B - pump_flow_rate_8 / 60 * frequency_;
    amount_of_tank_B = amount_of_tank_B - pump_flow_rate_B / 60 * frequency_;
    amount_of_tank_C = amount_of_tank_C - pump_flow_rate_1 / 60 * frequency_;
    amount_of_tank_C = amount_of_tank_C + pump_flow_rate_5 / 60 * frequency_;
    amount_of_tank_D = amount_of_tank_D - pump_flow_rate_3 / 60 * frequency_;
    amount_of_tank_D = amount_of_tank_D + pump_flow_rate_6 / 60 * frequency_;
    /* check full or empty */

    if( amount_of_tank_A > max_amount_of_tank_A )
    {
      amount_of_tank_A = max_amount_of_tank_A;
    }
    else if( amount_of_tank_A < 0 )
    {
      amount_of_tank_A = 0;
    }
    else
    {
    }

    if( amount_of_tank_B > max_amount_of_tank_B )
    {
      amount_of_tank_B = max_amount_of_tank_B;
    }
    else if( amount_of_tank_B < 0 )
    {
      amount_of_tank_B = 0;
    }
    else
    {
    }

    if( amount_of_tank_C > max_amount_of_tank_C )
    {
      amount_of_tank_C = max_amount_of_tank_C;
    }
    else if( amount_of_tank_C < 0 )
    {
      amount_of_tank_C = 0;
    }
    else
    {
    }

    if( amount_of_tank_D > max_amount_of_tank_D )
    {
      amount_of_tank_D = max_amount_of_tank_D;
    }
    else if( amount_of_tank_D < 0 )
    {
      amount_of_tank_D = 0;
    }
    else
    {
    }
  }

  void ResourceManagementTask::updateMatbEvent()
  {
    for( auto it = events_.begin(); it != events_.end(); ++it )
    {
      auto elapsed_time = MatbEventServer::elapsed_time();
      auto event_time   = std::chrono::duration_cast< std::chrono::nanoseconds >( it->get()->start_time() ).count();

      //     std::cout << int( it->get()->fail() ) << "," << int( it->get()->fix() ) << std::endl;

      if( ( elapsed_time - event_time ) >= 0 )
      {
        if( ResourceManagementEvent::Fail::P1 == it->get()->fail() )
        {
          valve_1_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P2 == it->get()->fail() )
        {
          valve_2_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P3 == it->get()->fail() )
        {
          valve_3_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P4 == it->get()->fail() )
        {
          valve_4_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P5 == it->get()->fail() )
        {
          valve_5_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P6 == it->get()->fail() )
        {
          valve_6_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P7 == it->get()->fail() )
        {
          valve_7_is_failed = true;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fail::P8 == it->get()->fail() )
        {
          valve_8_is_failed = true;
          events_.erase( it );
        }
        else
        {
        }

        if( ResourceManagementEvent::Fix::P1 == it->get()->fix() )
        {
          valve_1_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P2 == it->get()->fix() )
        {
          valve_2_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P3 == it->get()->fix() )
        {
          valve_3_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P4 == it->get()->fix() )
        {
          valve_4_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P5 == it->get()->fix() )
        {
          valve_5_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P6 == it->get()->fix() )
        {
          valve_6_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P7 == it->get()->fix() )
        {
          valve_7_is_failed = false;
          events_.erase( it );
        }
        else if( ResourceManagementEvent::Fix::P8 == it->get()->fix() )
        {
          valve_8_is_failed = false;
          events_.erase( it );
        }
        else
        {
        }

        break;
      }
      else
      {
      }
    }
  }

  void ResourceManagementTask::drawChainLine( cv::Mat img, cv::Point pt1, cv::Point pt2, const cv::Scalar& color, int thickness, int lineType, int shift )
  {
    cv::LineIterator it( img, pt1, pt2, 8 );

    for( int i = 0; i < it.count; i++, it++ )
    {
      if( i % 10 == 0 || i % 10 == 1 || i % 10 == 2 || i % 10 == 3 || i % 10 == 6 || i % 10 == 7 )
      {
        ( *it )[0] = color[0]; // Blue
        ( *it )[1] = color[1]; // Green
        ( *it )[2] = color[2]; // Red
      }
      else
      {
      }
    }
  }

};


