add_executable(
    unitTest
    main.cpp
    sanity.cpp
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