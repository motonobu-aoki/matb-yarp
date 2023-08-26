set( LIB_NAME "CommunicationsTaskThread" )
set( SOURCES
     communications_task_thread.cpp
     )
set( HEADERS
     communications_task_thread.hpp
     )
find_package( ICUB )
find_package( YARP COMPONENTS os sig cv )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
set_target_properties(
  ${LIB_NAME}
  PROPERTIES
  PUBLIC_HEADER
  ${HEADERS}
)
target_link_libraries( ${LIB_NAME}
                       ${YARP_LIBRARIES}
                       JoystickButtonSubscriber
                       CommunicationsTask
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
