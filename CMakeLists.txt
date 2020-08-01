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

# Hack: Eventually figure out how to change default install dir
set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/build")

# Set compile flags
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()


### Sub-Projects
include(ExternalProject)

ExternalProject_Add(glfw
  PREFIX GLFW
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party/GLFW"
  CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  )

ExternalProject_Add(engine
  PREFIX Engine
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine"
  CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  DEPENDS glfw
)

ExternalProject_Add(driver
  PREFIX Driver
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Driver"
  CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  INSTALL_COMMAND cmake -E echo "Skipping install step."
  DEPENDS engine
)
