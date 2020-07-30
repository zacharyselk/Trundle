cmake_minimum_required(VERSION 3.18.0)
project(Trundle C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
#set(CMAKE_VERBOSE_MAKEFILE true)

# Platform specific flags
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_WINDOWS")
elseif(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_MACOS")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_LINUX")
else()
  message(FATAL_ERROR "Error: Unknown platform, aborting.")
endif()

# Add some compiler flags based off of what build is being done
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

include(CMakeLists-Library.txt)