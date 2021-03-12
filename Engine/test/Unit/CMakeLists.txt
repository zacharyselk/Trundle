add_executable(
    unitTest
    main.cpp
    gtest.cpp
)

target_link_libraries(
    unitTest
    gtest_main
)

gtest_add_tests(
    unitTest
    ""
    AUTO
)