#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>  // EXPECT_FATAL_FAILURE

void fail() {
    ASSERT_TRUE(false) << "Expected failure";
}

TEST(sanity, gtest) {
    ASSERT_TRUE(true);
    ASSERT_FALSE(false);
}

TEST(sanity, insane) {
    EXPECT_FATAL_FAILURE(ASSERT_TRUE(false), "Expected");
}