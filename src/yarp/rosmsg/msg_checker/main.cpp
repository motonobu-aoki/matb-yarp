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
#include <yarp/os/all.h>
#include <yarp/rosmsg/std_msgs/String.h>
#include <yarp/rosmsg/geometry_msgs/Point.h>
#include <yarp/rosmsg/matb_msgs/Point2D.h>
// #include <rosmsg/include/Strings.h>

using namespace yarp::os;
using namespace std;
int main( int argc, char* argv[] )
{
  yarp::os::Network                                      yarp;
  Node                                                   node( "/yarp/msg_checker" );
  //   yarp::os::Publisher<yarp::rosmsg::matb_msgs::Point> publisher;
  yarp::os::Publisher <yarp::rosmsg::matb_msgs::Point2D> publisher;
  //   yarp::os::Publisher<yarp::rosmsg::matb_msgs::Points> publisher;

  if( !publisher.topic( "/msg_checker/pub" ))
  {
    cerr << "Failed to create publisher to /chatter\n";
    return -1;
  }
  while( true )
  {
    /* prepare some data */
    //     yarp::rosmsg::matb_msgs::Point msg;
    yarp::rosmsg::matb_msgs::Point2D msg;
    msg.x = 1;
    msg.y = 22;
    //     msg.z = 333;

    //     yarp::rosmsg::matb_msgs::Points msg;
    publisher.write( msg );
    Time::delay( 0.1 );
  }
  return 0;
}



