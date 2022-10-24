#include <iostream>
#include <gtest/gtest.h>
#include "../include/vector.h"

class VectorClass : public testing::Test {
 protected:
    Vector *_vectorVert;
    Vector *_vectorHoriz;

    void SetUp() {
        _vectorVert = new Vector({1, 2, 3}, true);
        _vectorHoriz = new Vector({1, 2, 3}, false);
    }

    void TearDown() {
        delete _vectorVert;
        delete _vectorHoriz;
    }
};

TEST(VectorInit, withNullArgs) {
    Vector vector;

    EXPECT_EQ(0, vector.getLen());
}

TEST(VectorInit, lenDirection) {
    Vector vector(4, false);

    EXPECT_EQ(4, vector.getLen());
    EXPECT_EQ(false, vector.getVerticalState());
}

TEST(VectorInit, byDoubleList) {
    Vector vector({1, 2, 3}, false);
    std::stringstream str;

    str << vector;

    EXPECT_STREQ("1 2 3", str.str().c_str());
}

TEST(VectorInit, byCopy) {
    Vector vector({1, 2, 3, 4}, false);
    Vector vector2(vector);
    std::stringstream str;

    str << vector2;

    EXPECT_STREQ("1 2 3 4", str.str().c_str());
}

TEST_F(VectorClass, getLen) {
    EXPECT_EQ(3, _vectorHoriz->getLen());
}

TEST_F(VectorClass, getDirection) {
    EXPECT_EQ(false, _vectorHoriz->getVerticalState());
}

TEST_F(VectorClass, sumVector) {
    std::stringstream str;
    Vector *tmp = *_vectorHoriz + *_vectorHoriz;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("2 4 6", str.str().c_str());
}

TEST_F(VectorClass, sumVectorDiffDirection) {
    Vector *tmp = *_vectorHoriz + *_vectorVert;

    EXPECT_EQ(nullptr, tmp);
}

TEST_F(VectorClass, sumOnIndexNumb) {
    std::stringstream str;
    Vector *tmp = _vectorVert->sumOn(0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("6\n2\n3", str.str().c_str());
}

TEST_F(VectorClass, subVector) {
    std::stringstream str;
    Vector *tmp = *_vectorHoriz - *_vectorHoriz;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("0 0 0", str.str().c_str());
}

TEST_F(VectorClass, subVectorDiffDirection) {
    Vector *tmp = *_vectorHoriz - *_vectorVert;

    EXPECT_EQ(nullptr, tmp);
}

TEST_F(VectorClass, subOnIndexNumb) {
    std::stringstream str;
    Vector *tmp = _vectorVert->subOn(0, 5);

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("-4\n2\n3", str.str().c_str());
}

TEST_F(VectorClass, composElemVector) {
    std::stringstream str;
    Vector *tmp = *_vectorHoriz & *_vectorHoriz;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("1 4 9", str.str().c_str());
}

TEST_F(VectorClass, composElemVectorDiffDirection) {
    Vector *tmp = *_vectorHoriz & *_vectorVert;

    EXPECT_EQ(nullptr, tmp);
}

TEST_F(VectorClass, composVectorNumb) {
    std::stringstream str;
    Vector *tmp = *_vectorHoriz * 5;

    str << *(tmp);

    delete tmp;

    EXPECT_STREQ("5 10 15", str.str().c_str());
}

TEST_F(VectorClass, indexMatrix) {
    EXPECT_EQ(3, (*_vectorHoriz)[2]);
}

TEST_F(VectorClass, assignmentVector) {
    Vector tmp = *_vectorHoriz;
    std::stringstream str;

    str << tmp;

    EXPECT_STREQ("1 2 3", str.str().c_str());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
