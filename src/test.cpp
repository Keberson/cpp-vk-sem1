#include <iostream>
#include <gtest/gtest.h>
#include "../include/matrix.h"

class MatrixCalculatorTest : public testing::Test {
 protected:
    Matrix *_matrix;

    void SetUp() { _matrix = new Matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});}
    void TearDown() { delete _matrix;}
};

TEST_F(MatrixCalculatorTest, initTest) {
    std::stringstream str;
    str << *_matrix;

    EXPECT_STREQ("1 2 3\n4 5 6\n7 8 9\n", str.str().c_str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
