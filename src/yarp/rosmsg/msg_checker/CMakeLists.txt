set( CMAKE_CXX_FLAGS "-std=c++1y" )
set( EXE_NAME "MsgChecker" )
set( SOURCES
     main.cpp
     )
set( HEADERS
     )
find_package( YARP REQUIRED COMPONENTS sig cv )
find_package( ICUB )
find_package( OpenCV REQUIRED )
add_executable( ${EXE_NAME}
                ${HEADERS}
                ${SOURCES}
                )
target_link_libraries( ${EXE_NAME}
                       ${YARP_LIBRARIES}
                       ${OpenCV_LIBRARIES}
                       )
include_directories( ${OpenCV_INCLUDE_DIRS} )
install( TARGETS ${EXE_NAME} DESTINATION bin )

