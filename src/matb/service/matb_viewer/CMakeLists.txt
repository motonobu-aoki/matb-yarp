set( CMAKE_AUTOMOC ON )
set( EXE_NAME "MatbViewer" )
set( SOURCES
     main.cpp
     )
set( HEADERS
     )
find_package( YARP COMPONENTS os sig cv )
find_package( ICUB )
find_package( OpenCV REQUIRED )
find_package( Qt5Widgets )
find_package( Qt5OpenGL REQUIRED )
find_package( Qt5 COMPONENTS Widgets Declarative )
add_executable( ${EXE_NAME}
                ${HEADERS}
                ${SOURCES}
                )
target_link_libraries( ${EXE_NAME}
                       ${YARP_LIBRARIES}
                       ${OpenCV_LIBRARIES}
                       Qt5::Widgets
                       Qt5::OpenGL
                       ${QT_LIBRARIES}
                       MatbViewerWidget
                       )
include_directories( ${OpenCV_INCLUDE_DIRS} )
install( TARGETS ${EXE_NAME} DESTINATION bin )
set( CMAKE_INCLUDE_CURRENT_DIR ON )
