cmake_minimum_required(VERSION 3.18.0)
project(Trundle_Engine C CXX)

# Set C++ configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TRUNDLE_LIBDIR ${PROJECT_SOURCE_DIR}/../lib)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../lib)

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

set(GLFW_CXX_FLAGS "")
set(GLFW_LINKER_FLAGS "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GLFW_CXX_FLAGS}")

# TODO: Cleanup
#       Add hardcoded paths like this for the engine lib
set(GLFW_INCLUDE_DIR "${TRUNDLE_LIBDIR}/include/")
set(GLFW_LIBRARY_DIR "${TRUNDLE_LIBDIR}/lib/")
#find_library(GLFW_LIB_D  glfw3_d ${GLFW_LIBRARY_DIR})
find_library(GLFW_LIB    glfw3   ${GLFW_LIBRARY_DIR})
include_directories(${GLFW_INCLUDE_DIR})

# Build engine as a dynamic library
add_library(engine SHARED)
#find_package(glfw3 3.3 REQUIRED)
#target_link_libraries(engine ${GLFW_LIBRARY_DIR})
find_library(GLFW_LIB glfw3
  PATHS ${GLFW_LIBRARY_DIR})
#link_directories(${GLFW_LIBRARY_DIR})
message("FOUND LIB: ${GLFW_LIB}")
#add_library(glfw IMPORTED_LOCATION ${GLFW_LIB})
target_link_libraries(engine ${GLFW_LIB})
#target_link_libraries(engine glfw)

if(WIN32)
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
elseif(APPLE)
  # Frameworks needed to link static glfw3 lib
  target_link_libraries(engine "-framework OpenGL")
  target_link_libraries(engine "-framework Cocoa")
  target_link_libraries(engine "-framework IOKit")
else()
  find_package(OpenGL REQUIRED)
  target_link_libraries(engine ${OPENGL_LIBRARIES})
endif()

set_target_properties(engine PROPERTIES VERSION 1.0.0 SOVERSION 1)
install(TARGETS engine EXPORT engineConfig
  ARCHIVE DESTINATION ${TRUNDLE_LIBDIR}
  LIBRARY DESTINATION ${TRUNDLE_LIBDIR}
  RUNTIME DESTINATION ${TRUNDLE_LIBDIR})

add_subdirectory(src)


target_include_directories(engine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

#install(DIRECTORY ./ DESTINATION
#  ${CMAKE_INSTALL_INCLUDEDIR}/engine/include)
#install(EXPORT engineConfig DESTINATION share/engine/cmake)
#install(EXPORT engineConfig DESTINATION ${TRUNDLE_LIBDIR}/)

# TODO: Cleanup the path names
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include
    DESTINATION ${TRUNDLE_LIBDIR})
install(EXPORT engineConfig DESTINATION ${TRUNDLE_LIBDIR})
export(TARGETS engine FILE ${TRUNDLE_LIBDIR}/engineConfig.cmake)

# Because Windows is dumb
if(WIN32)
    install(TARGETS engine DESTINATION ${PROJECT_SOURCE_DIR}/../bin/)
endif()
