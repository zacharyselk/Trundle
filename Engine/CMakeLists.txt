cmake_minimum_required(VERSION 3.18.0)
project(Trundle_Engine C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TRUNDLE_LIBDIR ${PROJECT_SOURCE_DIR}/../lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)

# Debug
#set(CMAKE_VERBOSE_MAKEFILE true)

# Add some compiler flags based off of what build is being done
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

#set(CMAKE_CXX_FLAGS "-Wall -Wextra")
#set(CMAKE_CXX_FLAGS_DEBUG "-g")
#set(CMAKE_CXX_FLAGS_RELEASE "-O3")


# Build engine as a dynamic library
add_library(engine SHARED)

set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)
install(TARGETS engine EXPORT engineConfig
  ARCHIVE DESTINATION ${TRUNDLE_LIBDIR}
  LIBRARY DESTINATION ${TRUNDLE_LIBDIR}
  RUNTIME DESTINATION ${TRUNDLE_LIBDIR})

#add_subdirectory(include)
add_subdirectory(src)


target_include_directories(engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    )

install(DIRECTORY ./ DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/engine/include)
install(EXPORT engineConfig DESTINATION share/engine/cmake)
export(TARGETS engine FILE ${TRUNDLE_LIBDIR}/engineConfig.cmake)
