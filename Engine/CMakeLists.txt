cmake_minimum_required(VERSION 3.18.0)
project(Trundle_Engine C CXX)

set(CMAKE_BINARY_DIR "${CMAKE_INSTALL_PREFIX}")
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in ${CMAKE_INSTALL_PREFIX}/googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
  )
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
  WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download"
  )

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
  "${CMAKE_BINARY_DIR}/googletest-build"
  )

# The gtest/gmock targets carry header search path dependencies
# automatically when using CMake 2.8.11 or later. Otherwise we
# have to add them here ourselves.
if(CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include"
    "${gmock_SOURCE_DIR}/include"
    )
endif()


# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Setting common directories
set(TRUNDLE_BUILD_DIR CACHE PATH "The build directory for the Trundle superbuild")
if (NOT TRUNDLE_BUILD_DIR)
  set(TRUNDLE_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")
  message(FATAL_ERROR "Build dir defaults to: ${TRUNDLE_BUILD_DIR}\nSupport not added yet, aborting")
endif()
set(TRUNDLE_LIB_DIR "${TRUNDLE_BUILD_DIR}/lib")
set(TRUNDLE_BIN_DIR "${TRUNDLE_BUILD_DIR}/bin")
set(TRUNDLE_INCLUDE_DIR "${TRUNDLE_BUILD_DIR}/include")
set(TRUNDLE_SHARE_DIR "${TRUNDLE_BUILD_DIR}/share")

# GL3W path
set(TRUNDLE_GL3W_DIR CACHE PATH "Path to GL3W source directory")
if (NOT TRUNDLE_GL3W_DIR)
  # TODO: Check if default path exists
  set(TRUNDLE_GL3W_DIR "${TRUNDLE_BUILD_DIR}/GL3W")
  message(WARNING "TRUNDLE_GL3W_DIR not set, defaulting to ${TRUNDLE_GLW3_DIR}")
endif()

# ImGui path
set(TRUNDLE_IMGUI_DIR CACHE PATH "Path to ImGui source directory")
if (NOT TRUNDLE_IMGUI_DIR)
  # TODO: Check if default path exists
  set(TRUNDLE_IMGUI_DIR "${TRUNDLE_BUILD_DIR}/ImGui")
  message(WARNING "TRUNDLE_IMGUI_DIR not set, defaulting to ${TRUNDLE_IMGUI_DIR}")
endif()

# Eigen path
set(TRUNDLE_EIGEN_DIR CACHE PATH "Path to Eigen source directory")
if (NOT TRUNDLE_EIGEN_DIR)
  # TODO: Check if default path exists
  set(TRUNDLE_EIGEN_DIR "${TRUNDLE_BUILD_DIR}/Eigen")
  message(WARNING "TRUNDLE_EIGEN_DIR not set, defaulting to ${TRUNDLE_EIGEN_DIR}")
endif()



# Hack
set(TRUNDLE_THIRD_PARTY_DIR "${CMAKE_INSTALL_PREFIX}/../Third-Party")

# Platform specific flags
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_WINDOWS -DTRUNDLE_BUILD_LIB")
elseif(APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_MACOS")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_GLAGS} -DTRUNDLE_OS_LINUX")
else()
  message(FATAL_ERROR "Error: Unknown platform, aborting.")
endif()

# Compile flags
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Add some compiler flags based off of what build is being done
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()


# Build engine as a dynamic library
add_library(engine SHARED)
set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)

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
target_sources(engine PRIVATE ${IMGUI_SRC})
target_include_directories(engine PRIVATE "${TRUNDLE_IMGUI_DIR}")
# TODO: Remove
target_sources(engine PRIVATE "${TRUNDLE_IMGUI_DIR}/examples/imgui_impl_glfw.cpp")
target_sources(engine PRIVATE "${TRUNDLE_IMGUI_DIR}/examples/imgui_impl_opengl3.cpp")

# Eigen
target_include_directories(engine PRIVATE "${TRUNDLE_EIGEN_DIR}")

# Note: Removed for now, not working
#add_subdirectory(test)

# GLFW should be built to the build directory
find_library(GLFW_LIB glfw3 ${TRUNDLE_LIB_DIR} REQUIRED)
target_include_directories(engine PRIVATE ${TRUNDLE_INCLUDE_DIR})
target_link_libraries(engine ${GLFW_LIB})

# GL3W
file(GLOB GL3W_SRC
  "${TRUNDLE_GL3W_DIR}/src/*.c"
  "${TRUNDLE_GL3W_DIR}/src/*.cpp"
  "${TRUNDLE_GL3W_DIR}/src/*.cc"
)
target_include_directories(engine PRIVATE "${TRUNDLE_GL3W_DIR}/include")
target_sources(engine PRIVATE "${GL3W_SRC}")

# Link OpenGL
if(WIN32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
elseif(APPLE)
  target_link_libraries(engine "-framework OpenGL")
  target_link_libraries(engine "-framework Cocoa")
  target_link_libraries(engine "-framework IOKit")
  target_link_libraries(engine "-framework CoreVideo")
else()
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
endif()

# Add all the Engine header files from Engine/include
target_include_directories(engine PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(src)

# Copies the Engine header files to the build
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${TRUNDLE_BUILD_DIR})

if(UNIX)
  install(TARGETS engine DESTINATION ${TRUNDLE_LIB_DIR})
elseif(WIN32)
  # Windows cannot find dll's unless they are in the same dir
  install(TARGETS engine DESTINATION ${TRUNDLE_BIN_DIR})
endif()
