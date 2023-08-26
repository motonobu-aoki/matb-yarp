set( LIB_NAME "MatbModule" )
set( SOURCES
     matb_module.cpp
     )
set( HEADERS
     matb_module.hpp
     )
find_package( ICUB )
find_package( YARP COMPONENTS os sig cv )
find_package( Boost REQUIRED COMPONENTS system timer )
find_package( OpenCV REQUIRED )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
target_link_libraries( ${LIB_NAME}
                       ${YARP_LIBRARIES}
                       ${OpenCV_LIBRARIES}
                       CommunicationsTaskThread
                       ResourceManagementTaskThread
                       SchedulingDisplayThread
                       SystemMonitoringTaskThread
                       TrackingTaskThread
                       MatbEventServer
                       )
target_include_directories( ${LIB_NAME} INTERFACE
                            $<INSTALL_INTERFACE:include>
                            )
install( EXPORT target
         FILE matbConfig.cmake
         DESTINATION lib/cmake/matb
         )
install( TARGETS ${LIB_NAME}
         DESTINATION lib
         EXPORT target
         )
string( REPLACE ${PROJECT_SOURCE_DIR} "" INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
string( REPLACE "/src" "include" INSTALL_DIR ${INSTALL_DIR} )
install( FILES ${HEADERS} DESTINATION ${INSTALL_DIR} )
