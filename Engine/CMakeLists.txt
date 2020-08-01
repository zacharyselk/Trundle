cmake_minimum_required(VERSION 3.18.0)
project(Trundle_Engine C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TRUNDLE_BUILD_DIR "${CMAKE_INSTALL_PREFIX}")
set(TRUNDLE_LIB_DIR "${TRUNDLE_BUILD_DIR}/lib")
set(TRUNDLE_BIN_DIR "${TRUNDLE_BUILD_DIR}/bin")
set(TRUNDLE_INCLUDE_DIR "${TRUNDLE_BUILD_DIR}/include")

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


# Build engine as a dynamic library
add_library(engine SHARED)
set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)

add_subdirectory(src)

# GLFW should be built to the build directory
find_library(GLFW_LIB glfw3 ${TRUNDLE_LIB_DIR} REQUIRED)
target_include_directories(engine PRIVATE ${TRUNDLE_INCLUDE_DIR})
target_link_libraries(engine ${GLFW_LIB})

# Link OpenGL
if(WIN32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
elseif(APPLE)
  target_link_libraries(engine "-framework OpenGL")
  target_link_libraries(engine "-framework Cocoa")
  target_link_libraries(engine "-framework IOKit")
else()
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
endif()

# Add all the Engine header files from Engine/include
target_include_directories(engine PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Copies the Engine header files to the build
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${TRUNDLE_BUILD_DIR})

if(UNIX)
  install(TARGETS engine DESTINATION ${TRUNDLE_LIB_DIR})
elseif(WIN32)
  # Windows cannot find dll's unless they are in the same dir
  install(TARGETS engine DESTINATION ${TRUNDLE_BIN_DIR})
endif()
