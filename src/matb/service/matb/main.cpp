#include <iostream>
#include <stdio.h>
#include <matb/module/matb_module/matb_module.hpp>
#include <filesystem>

int main(int argc, char* argv[])
{
    yarp::os::Network yarp;

    matb::MatbModule module;

    yarp::os::ResourceFinder rf;
    rf.setDefault("name", "matb");
    rf.setDefault("resman", "true");
    rf.setDefault("sysmon", "true");
    rf.setDefault("track", "true");
    rf.setDefault("comm", "true");
    rf.setDefault("sched", "true");
    rf.setDefault("frequency", "30");

    std::filesystem::path current_file_path(__FILE__);
    std::filesystem::path current_directory = current_file_path.parent_path();

    std::string event_json_file = current_directory.string() + "/../../../../app/matb/json/matb_experiment.json";
    std::cout << "Loads the following event file:" << std::endl;
    std::cout << event_json_file << std::endl;
    rf.setDefault("event_json_file", event_json_file);
    rf.configure(argc, argv);
    rf.setVerbose(true);

    if(!module.runModule(rf))
    {
        std::cerr << "Error module did not start" << std::endl;
    }

    std::cout << "Main returning..." << std::endl;
    return 0;
}


