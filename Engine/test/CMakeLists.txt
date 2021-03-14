function(ADD_REGRESSION_TEST TEST_NAME SRC_FILE)
  add_executable(${TEST_NAME} ${SRC_FILE})
  target_compile_definitions(${TEST_NAME} PRIVATE "TESTING_BUILD")
  target_link_libraries(${TEST_NAME} gtest_main engine)

  if (WIN32)
    # copy the .dll file to the same folder as the executable
    add_custom_command(
      TARGET ${TEST_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      $<TARGET_FILE_DIR:engine>
      $<TARGET_FILE_DIR:${TEST_NAME}>)
  endif()

  target_include_directories(${TEST_NAME} PRIVATE "${TRUNDLE_INCLUDE_DIR}")

  if (${TEST_HEADLESS})
    target_compile_definitions(${TEST_NAME} PRIVATE "RUN_HEADLESS")
  endif()

  gtest_add_tests(${TEST_NAME} "" AUTO)
endfunction()

function(ADD_UNIT_TEST TEST_NAME SRC_FILE)
  add_executable(${TEST_NAME} ${SRC_FILE} ${CMAKE_SOURCE_DIR}/test/Unit/main.cpp)
  target_link_libraries(${TEST_NAME} gtest_main engine)
  target_include_directories(${TEST_NAME} PRIVATE "${TRUNDLE_INCLUDE_DIR}")
  if (WIN32)
    # copy the .dll file to the same folder as the executable
    add_custom_command(
      TARGET ${TEST_NAME} POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      $<TARGET_FILE_DIR:engine>
      $<TARGET_FILE_DIR:${TEST_NAME}>)
  endif()

  gtest_add_tests(${TEST_NAME} "" AUTO)
endfunction()


add_subdirectory(Driver)
add_subdirectory(Regression)
add_subdirectory(Unit)