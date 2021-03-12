#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>  // EXPECT_FATAL_FAILURE

void fail() {
    ASSERT_TRUE(false) << "Expected failure";
}

TEST(gtest, sane) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

TEST(gtest, insane) {
    EXPECT_FATAL_FAILURE(ASSERT_TRUE(false), "Expected");
}