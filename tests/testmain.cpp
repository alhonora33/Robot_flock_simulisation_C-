#include <gtest/gtest.h>
#include <stddef.h>

TEST(TestMain, test1) {
    EXPECT_EQ(1, 1);
}

TEST(TestMain, test2) {
    EXPECT_EQ(2, 2);
}


int testmain(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}