set( LIB_NAME "MatbEvent" )
set( SOURCES
     matb_event_base.cpp
     matb_event.cpp
     system_event.cpp
     system_monitoring_event.cpp
     resource_management_event.cpp
     scheduling_event.cpp
     communication_event.cpp
     )
set( HEADERS
     matb_event_base.hpp
     matb_event.hpp
     system_event.hpp
     system_monitoring_event.hpp
     resource_management_event.hpp
     scheduling_event.hpp
     communication_event.hpp
     )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
link_directories( ${Boost_LIBRARY_DIR} )
find_package( Boost REQUIRED COMPONENTS system timer )
target_link_libraries( ${LIB_NAME}
                       ${Boost_LIBRARIES}
                       )
target_include_directories( ${LIB_NAME} INTERFACE
                            #     $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include> )
install( EXPORT target
         FILE matbConfig.cmake
         DESTINATION lib/cmake/matb
         )
install( TARGETS ${LIB_NAME}
         DESTINATION lib
         EXPORT target
         )
string( REPLACE ${PROJECT_SOURCE_DIR}/src "" REL_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
install( FILES ${HEADERS}
         DESTINATION ${INSTALL_INCLUDE_DIR}/${REL_INSTALL_DIR} )

