set( CMAKE_AUTOMOC ON )
set( LIB_NAME "MatbViewerWidget" )
set( SOURCES
     matb_viewer_widget.cpp
     )
set( HEADERS
     matb_viewer_widget.hpp
     )
find_package( YARP COMPONENTS os sig cv )
find_package( ICUB )
find_package( OpenCV REQUIRED )
find_package( Qt5Widgets )
find_package( Qt5OpenGL REQUIRED )
find_package( Qt5 COMPONENTS Widgets Declarative )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
target_link_libraries( ${LIB_NAME}
                       ${YARP_LIBRARIES}
                       Qt5::Widgets
                       Qt5::OpenGL
                       ${QT_LIBRARIES}
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
