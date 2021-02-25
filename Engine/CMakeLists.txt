cmake_minimum_required(VERSION 3.14.0...3.17.0)
project(Trundle C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Platform specific flags
if(WIN32)
  message(DEBUG "Detected Windows OS as the build environment")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTRUNDLE_OS_WINDOWS")
  
  # Check to see which Windows compiler is being used 
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

# Default to debug mode (for now)
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# Set compile flags
if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()

# Make sure that git is installed
find_package(Git)
if(NOT GIT_FOUND)
  message(FATAL_ERROR
    "Git was not found! Make sure that you have git installed in your environment")
endif()



## Options
option(BUILD_TESTS "Build with tests" ON)
option(LOG_LEVEL "Logging verbosity" "3")


## Globals
set(TRUNDLE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")



FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
)

FetchContent_Declare(
  imgui
  GIT_REPOSITORY https://github.com/ocornut/imgui
)

FetchContent_Declare(
  gl3w
  GIT_REPOSITORY https://github.com/skaslev/gl3w
)

FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw
)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm
)

FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(imgui)
FetchContent_MakeAvailable(gl3w)
FetchContent_MakeAvailable(glfw)
FetchContent_MakeAvailable(glm)

# Build engine as a dynamic library
add_library(engine SHARED)
set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)
target_compile_definitions(engine PRIVATE "TRUNDLE_BUILD_LIB")
target_compile_definitions(engine PRIVATE "TRUNDLE_LOGGING_LEVEL=${LOG_LEVEL}")

target_link_libraries(engine PRIVATE glfw)

# Add all the Engine header files from Engine/include
target_include_directories(engine PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

add_subdirectory(include)
add_subdirectory(src)

if(BUILD_TESTS)
  enable_testing()
  include(GoogleTest)
  add_subdirectory(test)
endif()