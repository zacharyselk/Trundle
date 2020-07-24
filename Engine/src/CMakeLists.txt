add_subdirectory(Math)
add_subdirectory(Util)
add_subdirectory(Trundle)

target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
