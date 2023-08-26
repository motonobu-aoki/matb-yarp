cmake_minimum_required( VERSION 2.8.3 )
# cmake_minimum_required( VERSION 3.15 )
project( matb )

# color settings
string( ASCII 27 Esc )
set( ColourReset "${Esc}[m" )
set( ColourBold "${Esc}[1m" )
set( Red "${Esc}[31m" )
set( Green "${Esc}[32m" )
set( Yellow "${Esc}[33m" )
set( Blue "${Esc}[34m" )
set( Magenta "${Esc}[35m" )
set( Cyan "${Esc}[36m" )
set( White "${Esc}[37m" )
set( BoldRed "${Esc}[1;31m" )
set( BoldGreen "${Esc}[1;32m" )
set( BoldYellow "${Esc}[1;33m" )
set( BoldBlue "${Esc}[1;34m" )
set( BoldMagenta "${Esc}[1;35m" )
set( BoldCyan "${Esc}[1;36m" )
set( BoldWhite "${Esc}[1;37m" )

# version
set(MATB_MAJOR_VERSION 0)
set(MATB_MINOR_VERSION 1)
set(MATB_PATCH_VERSION 0)
set(MATB_VERSION
  ${MATB_MAJOR_VERSION}.${MATB_MINOR_VERSION}.${MATB_PATCH_VERSION})

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR cmake)
else()
  set(DEF_INSTALL_CMAKE_DIR lib/cmake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH
  "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


# CMake version check
# if(CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 9)
#   set( CMAKE_CXX_FLAGS "-std=c++2a" )
# else()
  set( CMAKE_CXX_FLAGS "-std=c++17" )
# endif()
message("${Cyan}" CMAKE_CXX_COMPILER_VERSION: ${CMAKE_CXX_COMPILER_VERSION} ${ColourReset} )

# find_package
find_package( YARP REQUIRED os sig cv)
#find_package( ICUB REQUIRED)
#find_package( ICUBcontrib REQUIRED )

# CMAKE_MODULE_PATH
list( APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH} )
#list( APPEND CMAKE_MODULE_PATH ${ICUB_MODULE_PATH} )
#list( APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH} )
list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

# include .cmake
include( YarpInstallationHelpers )
#include( ICUBcontribHelpers )
#include( ICUBcontribOptions )

#set CMAKE_INSTALL_PREFIX to the ICUBcontrib one; print warning if user modifies it
#icubcontrib_set_default_prefix()
add_definitions( ${YARP_DEFINES} )
include( CTest )
#include_directories( ${ICUB_INCLUDE_DIRS} )
include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

#uninstall setting
if( NOT TARGET uninstall )
  configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY )
  add_custom_target( uninstall
                     COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake )
endif()

set( TARGET_LIBRARIES )


find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


add_subdirectory( src )
add_subdirectory( app )
add_subdirectory( cmake )
