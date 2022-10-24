#include <iostream>
#include <gtest/gtest.h>
#include "../include/matrix.h"

class MatrixClass : public testing::Test {
 protected:
    Matrix *_matrix;
    Vector *_vectorVert;
    Vector *_vectorHoriz;

    void SetUp() {
        _matrix = new Matrix(3, 3, {1, 2, 3, 4, 6, 6, 7, 8, 9});
        _vectorVert = new Vector({1, 2, 3}, true);
        _vectorHoriz = new Vector({1, 2, 3}, false);
    }

    void TearDown() {
        delete _matrix;
        delete _vectorVert;
        delete _vectorHoriz;
    }
};

TEST(MatrixInit, withNullArgs) {
    Matrix matrix;

    EXPECT_EQ(0, matrix.getRows());
    EXPECT_EQ(0, matrix.getCols());
}

TEST(MatrixInit, rowsCols) {
    Matrix matrix(4, 2);

    EXPECT_EQ(4, matrix.getRows());
    EXPECT_EQ(2, matrix.getCols());
}

TEST(MatrixInit, byDoubleList) {
    Matrix matrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});
    std::stringstream str;

    str << matrix;

    EXPECT_STREQ("1 2 3\n4 5 6\n7 8 9\n", str.str().c_str());
}

TEST(MatrixInit, byVectorList) {
    Vector v1({1, 2, 3}, true);
    Vector v2({4, 5, 6}, true);
    Vector v3({7, 8, 9}, true);
    Vector v4({10, 11, 12}, true);
    Matrix matrix({v1, v2, v3, v4});
    std::stringstream str;

    str << matrix;

    EXPECT_STREQ("1 2 3\n4 5 6\n7 8 9\n10 11 12\n", str.str().c_str());
}

TEST(MatrixInit, byCopy) {
    Matrix matrix1(2, 2, {1, 2, 3, 4});
    Matrix matrix2(matrix1);
    std::stringstream str;

    str << matrix2;

    EXPECT_STREQ("1 2\n3 4\n", str.str().c_str());
}

TEST_F(MatrixClass, getRow) {
    std::stringstream str;
    Vector *tmp = _matrix->getRow(0);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("1 2 3", str.str().c_str());
}

TEST_F(MatrixClass, getCol) {
    std::stringstream str;
    Vector *tmp = _matrix->getCol(0);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("1\n4\n7", str.str().c_str());
}

TEST_F(MatrixClass, getDiag) {
    std::stringstream str;
    Vector *tmp = _matrix->getDiag();

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("1\n6\n9", str.str().c_str());
}

TEST_F(MatrixClass, transpon) {
    Matrix tmp = *_matrix;
    std::stringstream str;

    tmp.tr();
    str << tmp;

    EXPECT_STREQ("1 4 7\n2 6 8\n3 6 9\n", str.str().c_str());
}

TEST_F(MatrixClass, determinant) {
    EXPECT_EQ(-12, _matrix->det());
}

TEST_F(MatrixClass, inverse) {
    std::stringstream str;
    Matrix *tmp = _matrix->inv();

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("-0.5 -0.5 0.5\n-0.5 1 -0.5\n0.833333 -0.5 0.166667\n", str.str().c_str());
}

TEST_F(MatrixClass, sumMatrix) {
    std::stringstream str;
    Matrix *tmp = *_matrix + *_matrix;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("2 4 6\n8 12 12\n14 16 18\n", str.str().c_str());
}

TEST_F(MatrixClass, sumOnRowColNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->sumOn(0, 0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("6 2 3\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, sumOnRowNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->sumOn(0, -1, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("6 7 8\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, sumOnColNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->sumOn(-1, 0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("6 2 3\n9 6 6\n12 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, sumOnRowVector) {
    std::stringstream str;
    Matrix *tmp = _matrix->sumOn(0, -1, *_vectorHoriz);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("2 4 6\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, sumOnColVector) {
    std::stringstream str;
    Matrix *tmp = _matrix->sumOn(-1, 0, *_vectorVert);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("2 2 3\n6 6 6\n10 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, subMatrix) {
    std::stringstream str;
    Matrix *tmp = *_matrix - *_matrix;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("0 0 0\n0 0 0\n0 0 0\n", str.str().c_str());
}

TEST_F(MatrixClass, subOnRowColNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->subOn(0, 0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("-4 2 3\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, subOnRowNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->subOn(0, -1, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("-4 -3 -2\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, subOnColNumb) {
    std::stringstream str;
    Matrix *tmp = _matrix->subOn(-1, 0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("-4 2 3\n-1 6 6\n2 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, subOnRowVector) {
    std::stringstream str;
    Matrix *tmp = _matrix->subOn(0, -1, *_vectorHoriz);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("0 0 0\n4 6 6\n7 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, subOnColVector) {
    std::stringstream str;
    Matrix *tmp = _matrix->subOn(-1, 0, *_vectorVert);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("0 2 3\n2 6 6\n4 8 9\n", str.str().c_str());
}

TEST_F(MatrixClass, composElemMatrix) {
    std::stringstream str;
    Matrix *tmp = *_matrix & *_matrix;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("1 4 9\n16 36 36\n49 64 81\n", str.str().c_str());
}

TEST_F(MatrixClass, composMatrixNumb) {
    std::stringstream str;
    Matrix *tmp = *_matrix * 5;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("5 10 15\n20 30 30\n35 40 45\n", str.str().c_str());
}

TEST_F(MatrixClass, composMatrixVectorVert) {
    std::stringstream str;
    Matrix *tmp = *_matrix * *_vectorVert;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("14\n34\n50\n", str.str().c_str());
}

TEST_F(MatrixClass, composMatrixVectorHoriz) {
    std::stringstream str;
    Matrix *tmp = *_matrix * *_vectorHoriz;

    EXPECT_EQ(nullptr, tmp);
}

TEST_F(MatrixClass, composMatrixMatrix) {
    std::stringstream str;
    Matrix *tmp = *_matrix * *_matrix;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("30 38 42\n70 92 102\n102 134 150\n", str.str().c_str());
}

TEST_F(MatrixClass, indexMatrix) {
    EXPECT_EQ(8, (*_matrix)[2][1]);
}

TEST_F(MatrixClass, assignmentMatrix) {
    Matrix tmp = *_matrix;
    std::stringstream str;

    str << tmp;

    EXPECT_STREQ("1 2 3\n4 6 6\n7 8 9\n", str.str().c_str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
