set( EXE_NAME "Matb" )
set( SOURCES
     main.cpp
     )
set( HEADERS
     )
find_package( YARP COMPONENTS os sig cv )
find_package( ICUB )
find_package( OpenCV REQUIRED )
add_executable( ${EXE_NAME}
                ${HEADERS}
                ${SOURCES}
                )
target_link_libraries( ${EXE_NAME}
                       ${YARP_LIBRARIES}
                       ${OpenCV_LIBRARIES}
                       MatbModule
                       )
include_directories( ${OpenCV_INCLUDE_DIRS} )
install( TARGETS ${EXE_NAME} DESTINATION bin )

