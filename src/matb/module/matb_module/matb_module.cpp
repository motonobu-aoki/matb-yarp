#include "matb_module.hpp"
namespace matb
{
    bool MatbModule::configure(yarp::os::ResourceFinder& _rf)
    {
        std::cout << " --- " << std::endl;

        MatbEventServer::init();
        MatbEventServer::parseMatbEventByJSON(_rf.find("matb_path").asString());
        events_ = MatbEventServer::system_events();
        key_press_event_subscriber_port.useCallback(key_press_event_subscriber);
        key_press_event_subscriber_port.setReplier(key_press_event_subscriber);
        key_press_event_subscriber_port.open("/" + _rf.find("name").asString() + "/key_press_event/sub");
        experiment_window_elapsed_time_subscriber_port_.useCallback(experiment_window_elapsed_time_subscriber_);
        experiment_window_elapsed_time_subscriber_port_.setReplier(experiment_window_elapsed_time_subscriber_);
        experiment_window_elapsed_time_subscriber_port_.open("/" + _rf.find("name").asString() + "/experiment_controller/elapsed_time/sub");

        period_ = 1.0 / _rf.find("frequency").asInt32();
        resman_ = _rf.find("resman").asBool();
        comm_ = _rf.find("comm").asBool();
        sched_ = _rf.find("sched").asBool();
        sysmon_ = _rf.find("sysmon").asBool();
        track_ = _rf.find("track").asBool();
        condition_ = _rf.find("condition").asString();

//        if(condition_ == "non-social")
//        {
//            condition_ = "nonsocial";
//        }

        if(resman_)
        {
            resource_management_task_thread = std::make_shared<ResourceManagementTaskThread>(period_, _rf);
            resource_management_task_thread->PeriodicThread::start();
        }

        if(comm_)
        {
            communications_task_thread = std::make_shared<CommunicationsTaskThread>(period_, _rf);
            communications_task_thread->PeriodicThread::start();
        }


        if(sysmon_)
        {
            system_monitoring_task_thread = std::make_shared<SystemMonitoringTaskThread>(period_, _rf);
            system_monitoring_task_thread->PeriodicThread::start();
        }

        if(track_)
        {
            tracking_task_thread = std::make_shared<TrackingTaskThread>(period_, _rf);
            tracking_task_thread->PeriodicThread::start();
        }

        if(comm_||track_)
        {
            scheduling_display_thread = std::make_shared<SchedulingDisplayThread>(period_, _rf);
            scheduling_display_thread->PeriodicThread::start();
        }
        MatbEventServer::elapsed_time();
        /* wait */
//        std::this_thread::sleep_for(std::chrono::duration(std::chrono::seconds(5)));

        return true;
    }

    bool MatbModule::close()
    {

        if(resman_)
        {
            resource_management_task_thread->threadRelease();
        }

        if(track_)
        {
            tracking_task_thread->threadRelease();
        }

        if(sysmon_)
        {
            system_monitoring_task_thread->threadRelease();
        }

        if(sched_)
        {
            scheduling_display_thread->threadRelease();
        }

        if(comm_)
        {
            communications_task_thread->threadRelease();
        }
        std::cout << "Calling close function in MatbModule" << std::endl;

        key_press_event_subscriber_port.close();
        experiment_window_elapsed_time_subscriber_port_.close();

        /* cmake version more than 3.16 */
        std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(3000)));
        /* cmake version 3.10 or less */
        usleep(3000000);

        if(resman_)
        {
            resource_management_task_thread->PeriodicThread::stop();
        }

        if(track_)
        {
            tracking_task_thread->PeriodicThread::stop();
        }

        if(sysmon_)
        {
            system_monitoring_task_thread->PeriodicThread::stop();
        }

        if(sched_)
        {
            scheduling_display_thread->PeriodicThread::stop();
        }

        if(comm_)
        {
            communications_task_thread->PeriodicThread::stop();
        }

        std::cout << "calling stop function in MatbModule" << std::endl;

        return true;
    }

    double MatbModule::getPeriod()
    {
        return period_;
    }

    void MatbModule::eventStart()
    {
        if(resman_)
        {
            resource_management_task_thread->ResourceManagementTask::start();
        }

        if(track_)
        {
            tracking_task_thread->TrackingTask::start();
        }

        if(sysmon_)
        {
            system_monitoring_task_thread->SystemMonitoringTask::start();
        }

        if(sched_)
        {
            scheduling_display_thread->SchedulingDisplay::start();
        }

        if(comm_)
        {
            communications_task_thread->CommunicationsTask::start();
        }
    }

    void MatbModule::eventStop()
    {
        if(resman_)
        {
            resource_management_task_thread->ResourceManagementTask::stop();
        }

        if(track_)
        {
            tracking_task_thread->TrackingTask::stop();
        }

        if(sysmon_)
        {
            system_monitoring_task_thread->SystemMonitoringTask::stop();
        }

        if(sched_)
        {
            scheduling_display_thread->SchedulingDisplay::stop();
        }

        if(comm_)
        {
            communications_task_thread->CommunicationsTask::stop();
        }
    }

    void MatbModule::clockStart()
    {
        MatbEventServer::start();
    }

    void MatbModule::checkClockStart()
    {
    }

    void MatbModule::input()
    {
        key_press_event_ = key_press_event_subscriber.bottle();
//        std::cout << key_press_event_.text << std::endl;
    }

    void MatbModule::output()
    {
    }

    bool MatbModule::updateModule()
    {
        input();
        updateMatbEvent();

        if(!MatbEventServer::is_started())
        {
            if("s" == key_press_event_.text)
            {
                MatbEventServer::start();
            }
        }
        output();
        return true;
    }

    bool MatbModule::respond(const yarp::os::Bottle& command, yarp::os::Bottle& reply)
    {
        std::cout << "Got something, echo is on" << '\n';

        if(command.get(0).asString() == "quit")
        {
            return false;
        }
        else
        {
            reply = command;
        }

        return true;
    }

    bool MatbModule::interruptModule()
    {
        std::cout << "Interrupting your module, for port cleanup" << std::endl;
        return true;
    }


    void MatbModule::updateMatbEvent()
    {
        if(MatbEventServer::is_started())
        {
            for(auto it = events_.begin(); it != events_.end(); ++it)
            {
                if(!it->get()->checkDone())
                {
                    auto elapsed_time = MatbEventServer::elapsed_time();
                    auto event_time = std::chrono::duration_cast<std::chrono::nanoseconds>(it->get()->start_time()).count();

                    //         std::cout << event_time << std::endl;

                    if((elapsed_time - event_time) >= 0)
                    {
                        if(SystemEvent::Control::START == it->get()->control())
                        {
                            //             is_started = true;
                            std::cout << "start matb system" << std::endl;

                            eventStart();
                            it->get()->done();
                        }
                        else if(SystemEvent::Control::END == it->get()->control())
                        {
                            std::cout << "end matb system" << std::endl;
                            //             is_started = false;
                            eventStop();
                            it->get()->done();

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
                else
                {
                }
            }
        }
    }

};
