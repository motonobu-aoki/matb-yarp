set( LIB_NAME "ResourceManagementTask" )
set( SOURCES
     resource_management_task.cpp
     )
set( HEADERS
     resource_management_task.hpp
     )
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_library( ${LIB_NAME} SHARED
             ${SOURCES}
             ${HEADERS}
             )
target_link_libraries( ${LIB_NAME}
                       ${OpenCV_LIBS}
#                        MATBEventServer
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
