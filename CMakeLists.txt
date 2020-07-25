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

# Make the executable be placed in /build/
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(BUILD_SHARED_LIBS true)

# Build engine as a dynamic library
add_library(engine)
add_subdirectory(Engine)
set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)
install(TARGETS engine EXPORT engineConfig
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install(DIRECTORY ./ DESTINATION
        ${CMAKE_INSTALL_INCLUDEDIR}/engine)
install(EXPORT engineConfig DESTINATION share/engine/cmake)
export(TARGETS engine FILE engineConfig.cmake)

find_package(engine REQUIRED
    PATHS ${CMAKE_INSTALL_BINDIR})
add_subdirectory(Driver)
#target_link_libraries(driver engine)