cmake_minimum_required(VERSION 3.0.0)
project(Trundle VERSION 0.1.0)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
#set(CMAKE_VERBOSE_MAKEFILE true)

# ???
include(CTest)
enable_testing()

# Point to local paths for source code and header files
file(GLOB sourceFiles src/*.cpp)
add_executable(Trundle ${sourceFiles})
include_directories(include test)

# Search for the SDL2 library on the system
find_path(SDL2_INCLUDE_DIR
  NAMES "SDL.h" "SDL_assert.h" "SDL_error.h"
  PATHS "${CMAKE_FRAMEWORK_PATH}/include" "${CMAKE_SYSTEM_INCLUDE_PATH}"
  PATH_SUFFIXES "SDL2" "include")
find_library(SDL2_LIBRARY
  NAMES "SDL2")

#find_path(SDL2_IMAGE_INCLUDE_DIR
#  NAMES "SDL_image.h"
#  PAATHS "${CMAKE_FRAMEWORK_PATH}/include"
#  PATH_SUFFIXES "SDL2")
#find_library(SDL2_IMAGE_LIBRARY
#  NAMES "SDL2")

# Check to see if SDL2 was found
# TODO: Have a proper backup plan for if SDL2 is not found
if(NOT SDL2_INCLUDE_DIR)
  MESSAGE("SDL2 header not found")
else()
  MESSAGE(${SDL2_INCLUDE_DIR})
endif()

if(NOT SDL2_LIBRARY)
  MESSAGE("SDL2 libraries not found")
else()
  MESSAGE(${SDL2_LIBRARY})
endif()

# Point to the SDL2 headers and library
target_include_directories(Trundle PUBLIC ${SDL2_INCLUDE_DIR})
target_link_libraries(Trundle ${SDL2_LIBRARY}) 

# Set name and veersion of the project
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# ???
include(CPack)
