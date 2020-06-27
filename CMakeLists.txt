cmake_minimum_required(VERSION 3.0.0)
project(Trundle VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_VERBOSE_MAKEFILE true)

include(CTest)
enable_testing()

add_executable(Trundle src/main.cpp)
include_directories(include)

# TODO: Encapsolate these paths into a varable that can be defined during the build
include_directories(Trundle D:/lib/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2)
include_directories(Trundle D:/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/include/SDL2)
target_link_libraries(Trundle D:/lib/SDL2-2.0.12/x86_64-w64-mingw32/lib/libSDL2.dll.a)
target_link_libraries(Trundle D:/lib/SDL2_image-2.0.5/x86_64-w64-mingw32/lib/libSDL2_image.dll.a)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
