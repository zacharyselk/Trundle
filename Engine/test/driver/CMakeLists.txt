add_executable(
    application
    application.cpp
)

target_compile_definitions(application PRIVATE "TESTING_BUILD")
target_compile_definitions(engine PRIVATE "TRUNDLE_LOGGING_LEVEL=${LOG_LEVEL}")

target_link_libraries(
    application
    gtest_main
    engine
)

if (WIN32)
# copy the .dll file to the same folder as the executable
add_custom_command(
    TARGET application POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    $<TARGET_FILE_DIR:engine>
    $<TARGET_FILE_DIR:application>)
endif()

target_include_directories(
    application  PRIVATE "${TRUNDLE_INCLUDE_DIR}"
)

gtest_add_tests(
    application
    ""
    AUTO
)