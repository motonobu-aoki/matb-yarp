set( LIB_NAME "TrackingTaskThread" )
set( SOURCES
     tracking_task_thread.cpp
     )
set( HEADERS
     tracking_task_thread.hpp
     )
find_package( ICUB )
find_package( YARP COMPONENTS os sig cv )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
target_link_libraries( ${LIB_NAME}
                       ${YARP_LIBRARIES}
                       TrackingTask
                       JoystickAxisSubscriber
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
