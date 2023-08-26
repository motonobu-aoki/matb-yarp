#include "scheduling_display_thread.hpp"
namespace matb
{

  SchedulingDisplayThread::SchedulingDisplayThread( const double& _period, yarp::os::ResourceFinder& _rf ) : PeriodicThread( _period )
  {
    rf_ = _rf;
  }

  SchedulingDisplayThread::~SchedulingDisplayThread()
  {
  }

  bool SchedulingDisplayThread::threadInit()
  {
    /* publisher */
    buffered_port.open( "/" + rf_.find( "name" ).asString() + "/scheduling_display/image/pub" );
    return true;
  }

  void SchedulingDisplayThread::threadRelease()
  {
    /* subscriber */

    /* publisher */
    buffered_port.close();
    std::cout << "Calling close function in SchedulingDisplayThread\n";
    return;
  }

  void SchedulingDisplayThread::afterStart( bool _success )
  {
  }

  void SchedulingDisplayThread::input()
  {
  }

  void SchedulingDisplayThread::output()
  {
    /* publisher */
    buffered_port.prepare() = yarp::cv::fromCvMat< yarp::sig::PixelRgb >( cv_image );
    buffered_port.write();
  }

  void SchedulingDisplayThread::run()
  {
    input();
    update();
    output();
  }

};

