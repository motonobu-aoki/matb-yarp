#include <iostream>
#include <cstdio>

/* c++ */
#include <iostream>
#include <cstdio>
#include <thread>
#include <vector>
#include <deque>
#include <chrono>
#include <mutex>
#include <chrono>
#include <memory>
#include <csignal>


/* boost */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <qt5/QtWidgets/QApplication>
#include <qt5/QtWidgets/QWidget>
#include <qt5/QtWidgets/QLabel>
#include <qt5/QtWidgets/QSlider>
#include <qt5/QtWidgets/QVBoxLayout>
#include <matb/Qt/qt_widget/matb_viewer_widget/matb_viewer_widget.hpp>

namespace
{
  bool flag = true;
  volatile std::sig_atomic_t gSignalStatus;
  matb::MatbViewerWidget* matb_viewer_widget;
}

void signal_handler( int signal )
{
  gSignalStatus = signal;

  if( SIGINT == signal )
  {
    delete matb_viewer_widget;
  }
}

int main( int argc, char* argv[] )
{
  QApplication     app( argc, argv );
  yarp::os::Network        yarp;
  yarp::os::ResourceFinder resource_finder;
  resource_finder.setDefault( "name", "matb_viewer" );
  resource_finder.setDefault( "width", "450" );
  resource_finder.setDefault( "height", "450" );
  resource_finder.configure( argc, argv );
  resource_finder.setVerbose( true );
  matb_viewer_widget = new matb::MatbViewerWidget( resource_finder );
  matb_viewer_widget->setGeometry( 100, 100, 1500, 1000 );
  matb_viewer_widget->setWindowTitle( "Multi Attribute Task Battery" );

  std::signal( SIGINT, signal_handler );

  matb_viewer_widget->show();
  app.exec();
  exit( 1 );
}







