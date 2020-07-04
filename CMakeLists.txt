cmake_minimum_required(VERSION 3.0.0)
project(Trundle VERSION 0.1.0)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
set(CMAKE_VERBOSE_MAKEFILE true)

# ???
include(CTest)
enable_testing()

# Point to local paths for source code and header files
add_executable(Trundle src/main.cpp)
include_directories(include)

# Search for the SDL2 library on the system
find_path(SDL2_INCLUDE_DIR
  NAMES "SDL.h" "SDL_assert.h" "SDL_error.h"
  PAATHS "${CMAKE_FRAMEWORK_PATH}/include"
  PATH_SUFFIXES "SDL2")
find_library(SDL2_LIBRARY
  NAMES "SDL2")

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

# TODO: Encapsolate these paths into a varable that can be defined during the build
#include_directories(Trundle D:/lib/SDL2-2.0.12/x86_64-w64-mingw32/include)
#include_directories(Trundle D:/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/include)
#target_link_libraries(Trundle D:/lib/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2.dll.a)
#target_link_libraries(Trundle D:/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/libSDL2_image.dll.a)

# Set name and veersion of the project
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

# ???
include(CPack)
