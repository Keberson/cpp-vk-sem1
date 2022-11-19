#include <iostream>
#include <gtest/gtest.h>
#include "../include/set.h"

TEST(TestInit, withNullArgs) {
    Set<int> new_set;

    EXPECT_EQ(0, new_set.size());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
