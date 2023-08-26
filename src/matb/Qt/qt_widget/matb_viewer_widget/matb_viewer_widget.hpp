#pragma once

/* c++ */
#include <iostream>
#include <cstdio>
#include <thread>
#include <vector>
#include <deque>
#include <mutex>
#include <chrono>
#include <memory>
#include <csignal>

/* boost */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

/* cv */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
/* qt */
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QSlider>
#include <qt5/QtWidgets/QVBoxLayout>
#include <qt5/QtWidgets/QOpenGLWidget>
#include <qt5/QtCore/QString>
#include <qt5/QtGui/QKeyEvent>
#include <qt5/QtGui/QtGui>
#include <yarp/cv/Cv.h>
#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/rosmsg/matb_msgs/QKey.h>
#include <matb/yarp_subscriber/yarp_subscriber/yarp_subscriber.hpp>
namespace matb
{
  class MatbViewerWidget : public QWidget
  {
      Q_OBJECT
    public:
      MatbViewerWidget( yarp::os::ResourceFinder& rf );
      ~MatbViewerWidget();

      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> resman_image_subscriber_;
      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> resman_status_image_subscriber_;
      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> sysmon_image_subscriber_;
      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> tracking_image_subscriber_;
      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> sched_image_subscriber_;
      matb::YarpSubscriber <yarp::sig::ImageOf< yarp::sig::PixelRgb >> comm_image_subscriber_;

      /*sub*/
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> resman_image_subscriber_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> resman_status_image_subscriber_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> sysmon_image_subscriber_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> tracking_image_subscriber_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> sched_image_subscriber_buffered_port_;
      yarp::os::BufferedPort <yarp::sig::ImageOf< yarp::sig::PixelRgb >> comm_image_subscriber_buffered_port_;

      /*pub*/
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_press_event_publisher_buffered_port_;
      yarp::os::BufferedPort <yarp::rosmsg::matb_msgs::QKey> key_release_event_publisher_buffered_port_;
      QVBoxLayout vbox_layout_;

    protected:
      void init();

      QBasicTimer q_basic_timer_;
      QHBoxLayout above_layout_;
      QHBoxLayout below_layout_;

      QLabel      resman_label_;
      QLabel      resman_status_label_;
      QLabel      sysmon_label_;
      QLabel      tracking_label_;
      QLabel      comm_label_;
      QLabel      sched_label_;

      int width_  = 100;
      int height_ = 100;

      virtual void close();
      virtual void closeEvent( QCloseEvent* _event ) override;
      virtual void leaveEvent( QEvent* event ) override;
      virtual void mousePressEvent( QMouseEvent* _event ) override;
      virtual void mouseMoveEvent( QMouseEvent* _event ) override;
      virtual void mouseDoubleClickEvent( QMouseEvent* _event ) override;
      virtual void wheelEvent( QWheelEvent* _event ) override;
      virtual void timerEvent( QTimerEvent* _event ) override;
      virtual void paintEvent( QPaintEvent* _event ) override;
      virtual void keyPressEvent( QKeyEvent* _event ) override;
      virtual void keyReleaseEvent( QKeyEvent* _event ) override;
  };

};
