cmake_minimum_required(VERSION 3.18.0)
project(Trundle_Driver C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../bin)

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

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(engine REQUIRED
  PATHS ${PROJECT_SOURCE_DIR}/../lib)
add_subdirectory(src)
target_link_libraries(driver engine)
find_package(glfw3 3.3 REQUIRED)
target_link_libraries(driver glfw)

message("Installing stuff to ${PROJECT_SOURCE_DIR}/../bin")
#install (TARGETS driver DESTINATION ${PROJECT_SOURCE_DIR}/../bin)