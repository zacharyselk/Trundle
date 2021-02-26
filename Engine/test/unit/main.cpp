#include <gtest/gtest.h>
#include <stdio.h>

int main(int argc, char **argv) {
    printf("Hello world");
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}