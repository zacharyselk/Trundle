add_executable(
    application
    application.cpp
)

target_link_libraries(
    application
    gtest_main
    #engine
)

target_include_directories(
    application  PRIVATE "${TRUNDLE_INCLUDE_DIR}"
)

gtest_add_tests(
    application
    ""
    AUTO
)