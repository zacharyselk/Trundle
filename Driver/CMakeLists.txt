cmake_minimum_required(VERSION 3.17.0)
project(Trundle_Driver C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TRUNDLE_BUILD_DIR "${CMAKE_INSTALL_PREFIX}")
set(TRUNDLE_LIB_DIR "${TRUNDLE_BUILD_DIR}/lib")
set(TRUNDLE_BIN_DIR "${TRUNDLE_BUILD_DIR}/bin")
set(TRUNDLE_INCLUDE_DIR "${TRUNDLE_BUILD_DIR}/include")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${TRUNDLE_BIN_DIR}")

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

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set compile flags
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -lpthread")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

if(LGTM_BUILD)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lGLEW")
endif()

# GLM path
set(TRUNDLE_GLM_DIR CACHE PATH "Path to GLM source directory")
if (NOT TRUNDLE_GLM_DIR)
  # TODO: Check if default path exists
  set(TRUNDLE_GLM_DIR "${TRUNDLE_BUILD_DIR}/GLM")
  message(WARNING "TRUNDLE_GLM_DIR not set, defaulting to ${TRUNDLE_GLM_DIR}")
endif()

# ImGui path
set(TRUNDLE_IMGUI_DIR CACHE PATH "Path to ImGui source directory")
if (NOT TRUNDLE_IMGUI_DIR)
  # TODO: Check if default path exists
  set(TRUNDLE_IMGUI_DIR "${TRUNDLE_BUILD_DIR}/ImGui")
  message(WARNING "TRUNDLE_IMGUI_DIR not set, defaulting to ${TRUNDLE_IMGUI_DIR}")
endif()

add_subdirectory(src)

# Find and link the engine library and include files
find_library(ENGINE_LIB engine "${TRUNDLE_LIB_DIR}" REQUIRED)
target_link_libraries(driver "${ENGINE_LIB}")
target_include_directories(driver PRIVATE "${TRUNDLE_INCLUDE_DIR}")

# GLM
target_include_directories(driver PRIVATE "${TRUNDLE_GLM_DIR}")

# ImGui
file(GLOB IMGUI_SRC
  "${TRUNDLE_IMGUI_DIR}/*.c"
  "${TRUNDLE_IMGUI_DIR}/*.cpp"
  "${TRUNDLE_IMGUI_DIR}/*.cc"
)
file(GLOB IMGUI_INCLUDE
  "${TRUNDL_IMGUI_DIR}/*.h"
  "${TRUNDL_IMGUI_DIR}/*.hpp"
)
target_sources(driver PRIVATE ${IMGUI_SRC})
target_include_directories(driver PRIVATE "${TRUNDLE_IMGUI_DIR}")
#target_sources(driver PRIVATE "${TRUNDLE_IMGUI_DIR}/examples/imgui_impl_glfw.cpp")
#target_sources(driver PRIVATE "${TRUNDLE_IMGUI_DIR}/examples/imgui_impl_opengl3.cpp")

# Deal with Visual Studio putting the exe in stupid places
if(MSVC)
  set_target_properties(driver PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${TRUNDLE_BIN_DIR}")
  set_target_properties(driver PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TRUNDLE_BIN_DIR}")
  set_target_properties(driver PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE "${TRUNDLE_BIN_DIR}")
endif(MSVC)

install (TARGETS driver DESTINATION "${TRUNDLE_BIN_DIR}")
