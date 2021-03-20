add_executable(driver driver.cpp)
target_link_libraries(driver engine)
if (WIN32)
  # copy the .dll file to the same folder as the executable
  add_custom_command(
    TARGET driver POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:engine>
    $<TARGET_FILE_DIR:driver>)
endif()
target_include_directories(driver PRIVATE "${TRUNDLE_INCLUDE_DIR}")