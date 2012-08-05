cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

# set static runtime library for MSVC
set(CMAKE_USER_MAKE_RULES_OVERRIDE
   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/c_flag_overrides.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE_CXX
   ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/cxx_flag_overrides.cmake)

project(tournament)

# rip off annoyng messages for MSVC
add_definitions(-D_CRT_SECURE_NO_DEPRECATE)
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_definitions(-D_CRT_NONSTDC_NO_WARNING)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

# Path to additional CMake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake${CMAKE_MODULE_PATH})
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules ${CMAKE_MODULE_PATH})

include(SociUtilities)

message(STATUS "")
colormsg(_HIBLUE_ "Configuring Tournament:")
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE ON)

# Tournament version information
include(SociVersion)
soci_version(MAJOR 0 MINOR 0 PATCH 1)

# Tournament dependances
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

if(WIN32)
# Configure BOOST
#
# Folowing make CMake search boost libraries with names
#  * libboost_libname-<toolsetname>-mt-sgd-<boostversion>.lib
#  * libboost_libname-<toolsetname>-mt-s-<boostversion>.lib
# in folder given by BOOST_ROOT environment variable
#
# Note: make sure that <toolsetname> part is matching 
# with the actual generator used in cmake!
#
set(BOOST_ROOT  C:/boost/104601  CACHE PATH  "Boost include path")
endif()

# Search for required libraries
find_package( Boost 1.39.0 COMPONENTS program_options REQUIRED )
find_package( Qt4 4.7 COMPONENTS QtCore QtGui QtDeclarative REQUIRED )
#include(${QT_USE_FILE})

# Put the link library paths here
link_directories (${Boost_LIBRARY_DIRS})

# Put the include library paths here
include_directories( ${PROJECT_SOURCE_DIR} )
include_directories( ${Boost_INCLUDE_DIRS} )

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(libs)
add_subdirectory(form_pairs)
add_subdirectory(start_round)
add_subdirectory(gui)
