message("Trunk")

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

# Download and build dependencies
set(TRUNDLE_BUILD_DIR "${PROJECT_BINARY_DIR}")
#configure_file(CMakeLists.txt.in "${TRUNDLE_BUILD_DIR}/CMakeLists.txt")

# execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" "../tmp"
#   WORKING_DIRECTORY "${TRUNDLE_BUILD_DIR}"
# )
# message("Four")
# execute_process(COMMAND "${CMAKE_COMMAND}" --build .
#   WORKING_DIRECTORY "${TRUNDLE_BUILD_DIR}"
# )

include(ExternalProject)

ExternalProject_Add(glfw
  PREFIX GLFW
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party/GLFW"
  CMAKE_CACHE_ARGS
      -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
)

# ExternalProject_Add(gl3w
#   GIT_REPOSITORY "https://github.com/skaslev/gl3w"
#   GIT_TAG "master"
#   #SOURCE_DIR "${CMAKE_INSTALL_PREFIX}/gl3w/src"
#   #BINARY_DIR "${CMAKE_INSTALL_PREFIX}/gl3w/bin"
#   #SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Third-Party/gl3w"
#   CMAKE_CACHE_ARGS
#   -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
# )

include(FetchContent)

# FetchContent_Declare(GL3W
#   GIT_REPOSITORY "https://github.com/skaslev/gl3w"
#   GIT_TAG "master"
# )
# FetchContent_Declare(ImGui
#   GIT_REPOSITORY "https://github.com/ocornut/imgui"
#   GIT_TAG "v1.77"
# )
# FetchContent_Populate(GL3W)
# FetchCOntent_Populate(ImGui)

# ExternalProject_Add(imgui
#   GIT_REPOSITORY "https://github.com/ocornut/imgui"
#   GIT_TAG "v1.77"
#   SOURCE_DIR "ImGui"
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND ""
#   INSTALL_COMMAND ""
#   TEST_COMMAND ""
# )

ExternalProject_Add(imgui
  GIT_REPOSITORY "https://github.com/ocornut/imgui"
  GIT_TAG "v1.77"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/ImGui"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND ""
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  )

ExternalProject_Add(gl3w
  GIT_REPOSITORY "https://github.com/skaslev/gl3w"
  GIT_TAG "master"
  SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/gl3w-download"
  BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/GL3W"
  INSTALL_DIR "${CMAKE_CURRENT_BINARY_DIR}/gl3w-install"
  INSTALL_COMMAND ""
  TEST_COMMAND ""
  )

# ExternalProject_Add(gtes
#   GIT_REPOSITORY "https://github.com/google/googletest.git"
#   GIT_TAG "master"
#   SOURCE_DIR "${CMAKE_INSTALL_PREFIX}/googletest/src"
#   BINARY_DIR "${CMAKE_INSTALL_PREFIX}/googletest/bin"
#   CONFIGURE_COMMAND ""
#   BUILD_COMMAND ""
#   INSTALL_COMMAND ""
#   TEST_COMMAND ""i
#   #CMAKE_CACHE_ARGS
#   #-DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
# )

ExternalProject_Add(engine
  PREFIX Engine
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine"
  CMAKE_ARGS list(APPEND CMAKE_ARGS "-DTRUNDLE_BUILD_DIR=${CMAKE_CURRENT_BINARY_DIR}")
  CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  DEPENDS glfw gl3w imgui
)
# FetchContent_Declare(ImGui
#   GIT_REPOSITORY "https://github.com/ocornut/imgui"
#   GIT_TAG "v1.77"
# )
# FetchContent_MakeAvailable(GL3W)


ExternalProject_Add(driver
  PREFIX Driver
  SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Driver"
  CMAKE_CACHE_ARGS
        -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
  INSTALL_COMMAND cmake -E echo "Skipping install step."
  DEPENDS engine
)

# ExternalProject_Add(testing
#   PREFIX Testing
#   SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Engine/test"
#   CMAKE_CACHE_ARGS
#       -DCMAKE_INSTALL_PREFIX:PATH=${CMAKE_INSTALL_PREFIX}
# )
