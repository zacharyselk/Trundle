cmake_minimum_required(VERSION 3.18.0)
project(Trundle C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Debug
#set(CMAKE_VERBOSE_MAKEFILE true)

# Add some compiler flags based off of what build is being done
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")

option(BUILD_LIB "Build dynamic library" ON)

if(BUILD_LIB)
  add_subdirectory(Engine)
else()
  add_subdirectory(Driver)
endif()


# # Make the executable be placed in /build/
# set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# set(BUILD_SHARED_LIBS true)

# #include(ExternalProject)
# #include(External_engine)
# #find_package(Engine REQUIRED
# #    PATHS ${CMAKE_BINARY_DIR})
# add_subdirectory(Driver)
# target_link_libraries(driver Engine)
