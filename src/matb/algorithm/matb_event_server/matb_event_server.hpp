#pragma once

/* c++ */
#include <iostream>
#include <cstdio>
#include <thread>
#include <vector>
#include <deque>
#include <chrono>
#include <mutex>

/* boost */
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/timer/timer.hpp>
#include <matb/algorithm/matb_event/matb_event.hpp>
#include <matb/algorithm/matb_event/system_event.hpp>
#include <matb/algorithm/matb_event/resource_management_event.hpp>
#include <matb/algorithm/matb_event/scheduling_event.hpp>
#include <matb/algorithm/matb_event/system_monitoring_event.hpp>
#include <matb/algorithm/matb_event/communication_event.hpp>
namespace matb
{
    class MatbEventServer
    {
    public:
        MatbEventServer();
        ~MatbEventServer();
    public:
        static void init();
        static void parseMatbEventByJSON(const std::string& _path);
        static bool is_started();
        static void start();
        static void stop();
        static void resume();
        static std::chrono::_V2::steady_clock::time_point start_time();
        static long elapsed_time();
        static std::deque <std::shared_ptr<MatbEventBase >> matb_base_events();
        static std::deque <std::shared_ptr<MatbEvent >> matb_events();
        static std::deque <std::shared_ptr<SystemEvent >> system_events();
        static std::deque <std::shared_ptr<ResourceManagementEvent >> resource_management_events();
        static std::deque <std::shared_ptr<SchedulingEvent >> scheduling_events();
        static std::deque <std::shared_ptr<SystemMonitoringEvent >> system_monitoring_events();
        static std::deque <std::shared_ptr<CommunicationEvent >> communication_events();
    protected:
        static bool is_started_;
        static bool is_parsed_;
        static bool is_initialized_;

        static std::recursive_mutex mutex_;
        static boost::property_tree::ptree matb_event_tree_;
        static std::chrono::_V2::steady_clock::time_point start_time_;
        static boost::timer::cpu_timer timer_;

        static std::deque <std::shared_ptr<MatbEventBase >> matb_base_events_;
        static std::deque <std::shared_ptr<MatbEvent >> matb_events_;
        static std::deque <std::shared_ptr<SystemEvent >> system_events_;
        static std::deque <std::shared_ptr<ResourceManagementEvent >> resource_management_events_;
        static std::deque <std::shared_ptr<SchedulingEvent >> scheduling_events_;
        static std::deque <std::shared_ptr<SystemMonitoringEvent >> system_monitoring_events_;
        static std::deque <std::shared_ptr<CommunicationEvent >> communication_events_;
    };
};
