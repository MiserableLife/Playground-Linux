cmake_minimum_required (VERSION 2.6)
set( PROJECT LTTngTest)
project (LTTngTest)
# The version number. 
set (${PROJECT}_VERSION_MAJOR 1)
set (${PROJECT}_VERSION_MINOR 0)

set(CMAKE_C_COMPILER "clang++") # set compiler

#build type configuration 
#Debug / Release / RelWithDebInfo / MinSizeRel
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_C_FLAGS_DEBUG "--std=c++11")# compile options only for Debug build type


include_directories(./)
# configure a header file to pass some of CMake settings to the src code


#setting source files
set(SOURCES TPprovider.cc application.cpp )


#add the executable
set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ./)

add_executable(${PROJECT} ${SOURCES})
TARGET_LINK_LIBRARIES( ${PROJECT}  lttng-ust dl)
#ADD_DEFINITIONS ( -DTHREADSAFE)

install (TARGETS ${PROJECT} DESTINATION .)
