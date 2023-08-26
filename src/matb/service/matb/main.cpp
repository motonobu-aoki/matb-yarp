#include <iostream>
#include <stdio.h>
#include <matb/module/matb_module/matb_module.hpp>

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
//    rf.setDefault("condition", "non_social");
//    std::string matb_path = getenv("YARP_INSTALL_DIR");
    std::string matb_path = getenv("ICUBcontrib_DIR");
    matb_path = matb_path + "/share/matb/json/matb_experiment.json";
//   matb_path = matb_path + "/share/matb/json/matb_experiment_long.json";
//   matb_path = matb_path + "/share/matb/matb/json/tracking_task.json";
    std::cout << matb_path << std::endl;
    rf.setDefault("matb_path", matb_path);
    rf.configure(argc, argv);
    rf.setVerbose(true);

    if(!module.runModule(rf))
    {
        std::cerr << "Error module did not start" << std::endl;
    }

    std::cout << "Main returning..." << std::endl;
    //   return module.runModule( rf );
    return 0;
}


