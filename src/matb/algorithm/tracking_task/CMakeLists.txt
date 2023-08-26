set( LIB_NAME "TrackingTask" )
set( SOURCES
     tracking_task.cpp
     )
set( HEADERS
     tracking_task.hpp
     )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
target_link_libraries( ${LIB_NAME}
#                        MatbEventServer
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
