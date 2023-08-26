#include "matb_event_server.hpp"

namespace matb
{
    /* static member variables */
    std::recursive_mutex                                     MatbEventServer::mutex_;
    boost::property_tree::ptree                              MatbEventServer::matb_event_tree_;
    std::chrono::_V2::steady_clock::time_point               MatbEventServer::start_time_;
    std::deque <std::shared_ptr<MatbEventBase >>            MatbEventServer::matb_base_events_;
    std::deque <std::shared_ptr<MatbEvent >>                MatbEventServer::matb_events_;
    std::deque <std::shared_ptr<SystemEvent >>              MatbEventServer::system_events_;
    std::deque <std::shared_ptr<ResourceManagementEvent >>  MatbEventServer::resource_management_events_;
    std::deque <std::shared_ptr<SchedulingEvent >>          MatbEventServer::scheduling_events_;
    std::deque <std::shared_ptr<SystemMonitoringEvent >>    MatbEventServer::system_monitoring_events_;
    std::deque <std::shared_ptr<CommunicationEvent >>       MatbEventServer::communication_events_;
    bool MatbEventServer::is_parsed_;
    bool MatbEventServer::is_started_;
    bool MatbEventServer::is_initialized_;
    boost::timer::cpu_timer MatbEventServer::timer_;

    void MatbEventServer::init()
    {
        if(!is_initialized_)
        {
            timer_.stop();
            is_parsed_ = false;
            is_started_ = false;
            is_initialized_ = true;
        }
    }

    MatbEventServer::MatbEventServer()
    {
        init();
    }

    MatbEventServer::~MatbEventServer()
    {
    }

    std::chrono::_V2::steady_clock::time_point MatbEventServer::start_time()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return start_time_;
    }

    long MatbEventServer::elapsed_time()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        long elapsed_time = 0;

        if(timer_.is_stopped())
        {
        }
        else
        {
            elapsed_time = timer_.elapsed().wall;
        }

        return elapsed_time;
    }

    bool MatbEventServer::is_started()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return is_started_;
    }

    void MatbEventServer::start()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);

        if(!is_started_)
        {
            start_time_ = std::chrono::steady_clock::now();
            timer_.start();
            is_started_ = true;
        }
    }

    void MatbEventServer::stop()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);

        if(is_started_)
        {
            timer_.stop();
            is_started_ = false;
        }
    }

    void MatbEventServer::resume()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);

        if(!is_started_)
        {
            timer_.resume();
            is_started_ = true;
        }
    }

    std::deque <std::shared_ptr<CommunicationEvent >> MatbEventServer::communication_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return communication_events_;
    }

    std::deque <std::shared_ptr<MatbEventBase >> MatbEventServer::matb_base_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return matb_base_events_;
    }

    std::deque <std::shared_ptr<MatbEvent >> MatbEventServer::matb_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return matb_events_;
    }

    std::deque <std::shared_ptr<ResourceManagementEvent >> MatbEventServer::resource_management_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return resource_management_events_;
    }

    std::deque <std::shared_ptr<SchedulingEvent >> MatbEventServer::scheduling_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return scheduling_events_;
    }

    std::deque <std::shared_ptr<SystemEvent >> MatbEventServer::system_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return system_events_;
    }

    std::deque <std::shared_ptr<SystemMonitoringEvent >> MatbEventServer::system_monitoring_events()
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);
        return system_monitoring_events_;
    }

    void MatbEventServer::parseMatbEventByJSON(const std::string& _path)
    {
        std::lock_guard <std::recursive_mutex> lock(mutex_);

        if(is_parsed_)
        {
        }
        else
        {
            //     std::string path = getenv( "YARP_INSTALL_DIR" );
            //     path = path + "/share/sscr/matb/json/system_monitoring_task.json";
            //     path = path + "/share/sscr/matb/json/multi_attribute_task_battery.json";
            //     path = path + "/share/sscr/matb/json/tracking_task.json";
            boost::property_tree::read_json(_path, matb_event_tree_);

            for(const auto& a : matb_event_tree_.get_child("MATB-EVENTS.event"))
            {
                std::shared_ptr <SystemEvent> system_event = std::make_shared<SystemEvent>();
                std::shared_ptr <ResourceManagementEvent> resource_management_event = std::make_shared<ResourceManagementEvent>();
                std::shared_ptr <SchedulingEvent> scheduling_event = std::make_shared<SchedulingEvent>();
                std::shared_ptr <SystemMonitoringEvent> system_monitoring_event = std::make_shared<SystemMonitoringEvent>();
                std::shared_ptr <CommunicationEvent> communication_event = std::make_shared<CommunicationEvent>();
                std::string start_time = a.second.get_optional<std::string>("_startTime").get();
                std::chrono::seconds seconds = std::chrono::seconds(std::stoi(start_time.substr(5)));
                std::chrono::minutes minutes = std::chrono::minutes(std::stoi(start_time.substr(2, 2)));
                std::chrono::hours hours = std::chrono::hours(std::stoi(start_time.substr(0, 1)));
                system_event->start_time(seconds + minutes + hours);
                resource_management_event->start_time(seconds + minutes + hours);
                scheduling_event->start_time(seconds + minutes + hours);
                system_monitoring_event->start_time(seconds + minutes + hours);
                communication_event->start_time(seconds + minutes + hours);

                for(const auto& b : a.second.get_child(""))
                {
                    if("control" == std::string(b.first.data()))
                    {
                        if("START" == b.second.data())
                        {
                            system_event->control(SystemEvent::Control::START);
                        }
                        else if("END" == b.second.data())
                        {
                            system_event->control(SystemEvent::Control::END);
                        }

                        system_events_.push_back(system_event);
                    }

                    if("wrs" == std::string(b.first.data()))
                    {
                        if("START" == b.second.data())
                        {
                            system_event->wrs(SystemEvent::WRS::START);
                        }
                        else if("END" == b.second.data())
                        {
                            system_event->wrs(SystemEvent::WRS::END);
                        }

                        system_events_.push_back(system_event);
                    }

                    if("comm" == std::string(b.first.data()))
                    {
                        auto ship = b.second.get_optional<std::string>("ship").get();

                        if("OWN" == ship)
                        {
                            communication_event->ship(CommunicationEvent::Ship::OWN);
                        }
                        else if("OTHER" == ship)
                        {
                            communication_event->ship(CommunicationEvent::Ship::OTHER);
                        }

                        auto radio = b.second.get_optional<std::string>("radio").get();

                        if("NAV1" == radio)
                        {
                            communication_event->radio(CommunicationEvent::Radio::NAV1);
                        }
                        else if("NAV2" == radio)
                        {
                            communication_event->radio(CommunicationEvent::Radio::NAV2);
                        }
                        else if("COM1" == radio)
                        {
                            communication_event->radio(CommunicationEvent::Radio::COM1);
                        }
                        else if("COM2" == radio)
                        {
                            communication_event->radio(CommunicationEvent::Radio::COM2);
                        }

                        auto freq = b.second.get_optional<std::string>("freq").get();
                        communication_event->freq(freq);
                        communication_events_.push_back(communication_event);
                    }

                    if("resman" == std::string(b.first.data()))
                    {
                        if(2 == b.second.get_optional<std::string>("fail")->size())
                        {
                            auto fail = b.second.get_optional<std::string>("fail").get();

                            if("P1" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P1);
                            }
                            else if("P2" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P2);
                            }
                            else if("P3" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P3);
                            }
                            else if("P4" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P4);
                            }
                            else if("P5" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P5);
                            }
                            else if("P6" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P6);
                            }
                            else if("P7" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P7);
                            }
                            else if("P8" == fail)
                            {
                                resource_management_event->fail(ResourceManagementEvent::Fail::P8);
                            }
                        }

                        if(2 == b.second.get_optional<std::string>("fix")->size())
                        {
                            auto fix = b.second.get_optional<std::string>("fix").get();

                            if("P1" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P1);
                            }
                            else if("P2" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P2);
                            }
                            else if("P3" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P3);
                            }
                            else if("P4" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P4);
                            }
                            else if("P5" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P5);
                            }
                            else if("P6" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P6);
                            }
                            else if("P7" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P7);
                            }
                            else if("P8" == fix)
                            {
                                resource_management_event->fix(ResourceManagementEvent::Fix::P8);
                            }
                        }

                        resource_management_events_.push_back(resource_management_event);
                    }

                    if("sched" == std::string(b.first.data()))
                    {
                        auto task = b.second.get_optional<std::string>("task").get();
                        auto action = b.second.get_optional<std::string>("action").get();
                        auto update = b.second.get_optional<std::string>("update").get();
                        auto response = b.second.get_optional<std::string>("response").get();

                        if("COMM" == task)
                        {
                            scheduling_event->task(SchedulingEvent::Task::COMM);
                        }
                        else if("RESMAN" == task)
                        {
                            scheduling_event->task(SchedulingEvent::Task::RESMAN);
                        }
                        else if("RESSYS" == task)
                        {
                            scheduling_event->task(SchedulingEvent::Task::RESSYS);
                        }
                        else if("SYSMON" == task)
                        {
                            scheduling_event->task(SchedulingEvent::Task::SYSMON);
                        }
                        else if("TRACK" == task)
                        {
                            scheduling_event->task(SchedulingEvent::Task::TRACK);
                        }

                        if("MANUAL" == action)
                        {
                            scheduling_event->action(SchedulingEvent::Action::MANUAL);
                        }
                        else if("AUTO" == action)
                        {
                            scheduling_event->action(SchedulingEvent::Action::AUTO);
                        }
                        else if("START" == action)
                        {
                            scheduling_event->action(SchedulingEvent::Action::START);
                        }
                        else if("STOP" == action)
                        {
                            scheduling_event->action(SchedulingEvent::Action::STOP);
                        }

                        if("LOW" == update)
                        {
                            scheduling_event->update(SchedulingEvent::Update::LOW);
                        }
                        else if("MEDIUM" == update)
                        {
                            scheduling_event->update(SchedulingEvent::Update::MEDIUM);
                        }
                        else if("HIGH" == update)
                        {
                            scheduling_event->update(SchedulingEvent::Update::HIGH);
                        }

                        if("LOW" == response)
                        {
                            scheduling_event->response(SchedulingEvent::Response::LOW);
                        }
                        else if("MEDIUM" == response)
                        {
                            scheduling_event->response(SchedulingEvent::Response::MEDIUM);
                        }
                        else if("HIGH" == response)
                        {
                            scheduling_event->response(SchedulingEvent::Response::HIGH);
                        }

                        scheduling_events_.push_back(scheduling_event);
                    }

                    if("sysmon" == std::string(b.first.data()))
                    {
                        auto monitoring_light_type = b.second.get_optional<std::string>("monitoringLightType").get();
                        auto monitoring_scale_number = b.second.get_optional<std::string>("monitoringScaleNumber").get();
                        auto monitoring_scale_direction = b.second.get_optional<std::string>("monitoringScaleDirection").get();

                        if("GREEN" == monitoring_light_type)
                        {
                            system_monitoring_event->monitoring_light_type(SystemMonitoringEvent::MonitoringLightType::GREEN);
                        }
                        else if("RED" == monitoring_light_type)
                        {
                            system_monitoring_event->monitoring_light_type(SystemMonitoringEvent::MonitoringLightType::RED);
                        }

                        if("ONE" == monitoring_scale_number)
                        {
                            system_monitoring_event->monitoring_scale_number(SystemMonitoringEvent::MonitoringScaleNumber::ONE);
                        }
                        else if("TWO" == monitoring_scale_number)
                        {
                            system_monitoring_event->monitoring_scale_number(SystemMonitoringEvent::MonitoringScaleNumber::TWO);
                        }
                        else if("THREE" == monitoring_scale_number)
                        {
                            system_monitoring_event->monitoring_scale_number(SystemMonitoringEvent::MonitoringScaleNumber::THREE);
                        }
                        else if("FOUR" == monitoring_scale_number)
                        {
                            system_monitoring_event->monitoring_scale_number(SystemMonitoringEvent::MonitoringScaleNumber::FOUR);
                        }

                        if("UP" == monitoring_scale_direction)
                        {
                            system_monitoring_event->monitoring_scale_direction(SystemMonitoringEvent::MonitoringScaleDirection::UP);
                        }
                        else if("DOWN" == monitoring_scale_direction)
                        {
                            system_monitoring_event->monitoring_scale_direction(SystemMonitoringEvent::MonitoringScaleDirection::DOWN);
                        }

                        system_monitoring_events_.push_back(system_monitoring_event);
                    }
                }
            }

            is_parsed_ = true;
        }
    }

};

