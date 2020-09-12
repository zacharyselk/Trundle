cmake_minimum_required(VERSION 3.17.0)
project(Trundle C CXX)


# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
#set(CMAKE_VERBOSE_MAKEFILE true)

option(LGTM_BUILD "" OFF)

# Platform specific flags
if(WIN32)
  message(DEBUG "Detected Windows OS as the build environment")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTRUNDLE_OS_WINDOWS")

  if(MINGW)
    message(DEBUG "Detected the MinGW compiler; switching to static standard libraries")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")
  elseif(MSVC)
    message(DEBUG "Detected the MSVC compiler")
  endif()
elseif(APPLE)
  message(DEBUG "Detected OSX as the build environment")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTRUNDLE_OS_MACOS")
elseif(UNIX)
  message(DEBUG "Detected Linux as the build environment")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTRUNDLE_OS_LINUX")
else()
  message(FATAL_ERROR "Error: Unknown platform, aborting.")
endif()

# Add some compiler flags based off of what build is being done
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set compile flags
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++17 -stdlib=libc++")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()


### Sub-Projects

# Make sure that git is installed
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR
    "Git was not found! Make sure that you have git installed in your environment")
endif()

# Download and build dependencies
set(TRUNDLE_BUILD_DIR "${PROJECT_BINARY_DIR}")

include(ExternalProject)

ExternalProject_Add(imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui"
  GIT_TAG "docking"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/ImGui"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  )

ExternalProject_Add(gl3w
  GIT_REPOSITORY "https://github.com/skaslev/gl3w"
  GIT_TAG "master"
  SOURCE_DIR "${TRUNDLE_BUILD_DIR}/gl3w-download"
  BINARY_DIR "${TRUNDLE_BUILD_DIR}/GL3W"
  INSTALL_DIR "${TRUNDLE_BUILD_DIR}/gl3w-install"
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  )

ExternalProject_Add(glfw
  GIT_REPOSITORY "https://github.com/glfw/glfw"
  GIT_TAG "master"
  SOURCE_DIR "${TRUNDLE_BUILD_DIR}/GLFW"
  BINARY_DIR "${TRUNDLE_BUILD_DIR}/GLFW"
  INSTALL_DIR "${TRUNDLE_BUILD_DIR}/GLFW"
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

ExternalProject_Add(glm
  GIT_REPOSITORY "https://github.com/g-truc/glm"
  GIT_TAG "master"
  SOURCE_DIR "${TRUNDLE_BUILD_DIR}/GLM"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
)

# ExternalProject_Add(gtest
#   GIT_REPOSITORY "https://github.com/google/googletest.git"
#   GIT_TAG "master"
#   SOURCE_DIR "${TRUNDLE_BUILD_DIR}/googletest/src"
#   BINARY_DIR "${TRUNDLE_BUILD_DIR}/googletest/bin"
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND ""
#   INSTALL_COMMAND ""
#   TEST_COMMAND ""
#   #CMAKE_CACHE_ARGS
#   #-DCMAKE_INSTALL_PREFIX:PATH=${TRUNDLE_BUILD_DIR}
# )

ExternalProject_Add(engine
  PREFIX Engine
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine"
  CMAKE_ARGS list(APPEND CMAKE_ARGS "-DTRUNDLE_BUILD_DIR=${TRUNDLE_BUILD_DIR}")
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${TRUNDLE_BUILD_DIR}
  DEPENDS glfw gl3w imgui glm
)

ExternalProject_Add(driver
  PREFIX Driver
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Driver"
  CMAKE_CACHE_ARGS
    -DCMAKE_INSTALL_PREFIX:PATH=${TRUNDLE_BUILD_DIR}
    -DLGTM_BUILD:BOOL=${LGTM_BUILD}
  INSTALL_COMMAND cmake -E echo "Skipping install step."
  DEPENDS engine
)

# ExternalProject_Add(testing
#   PREFIX Testing
#   SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine/test"
#   CMAKE_CACHE_ARGS
#       -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
# )
