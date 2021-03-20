target_compile_definitions(engine PRIVATE "TRUNDLE_LOGGING_LEVEL=${LOG_LEVEL}")

add_regression_test(application application.cpp)
add_regression_test(events events.cpp)
add_regression_test(layers layers.cpp)