
#find_library(GTEST_LIB gtest ${TRUNDLE_LIB_DIR} REQUIRED)
message("${TRUNDLE_LIB_DIR}/googletest-src/googletest/include")
include_directories(
  # TODO: Remove hardcoded path
  "${TRUNDLE_LIB_DIR}/../googletest-src/googletest/include"
  )

add_executable(unit_test tmp.cpp)
target_link_libraries(unit_test PUBLIC gtest gtest_main)
target_include_directories(unit_test PRIVATE ${TRUNDLE_INCLUDE_DIR})

add_test(NAME unit_test COMMAND unit_test)
