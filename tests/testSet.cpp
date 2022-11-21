#include <ctime>
#include <iostream>
#include <gtest/gtest.h>
#include <set>

#include "../include/set.h"

class OwnSet : public testing::Test {
protected:
    Set<int> *new_set;
    std::set<int> *std_set;

    OwnSet() {
        new_set = new Set<int>{5, 6, 4, -1, 0, 2};
        std_set = new std::set{5, 6, 4, -1, 0, 2};
    }

    ~OwnSet() {
        delete new_set;
        delete std_set;
    }
};

TEST(TestInit, withNullArgs) {
    Set<int> new_set;

    EXPECT_EQ(0, new_set.size());
}

TEST(TestInit, withInitList) {
    Set<int> new_set{1, 2, 4, 3, 8, 6, 5, 5};

    EXPECT_EQ(7, new_set.size());
    EXPECT_EQ(1, *new_set.begin());
    EXPECT_EQ(8, *new_set.end());
}

TEST(TestInit, withIteratorsArgs) {
    int arr[] = {1, 2, 3, 5, 5, 5, 5};
    Set<int> new_set(arr, arr + 6);

    EXPECT_EQ(4, new_set.size());
    EXPECT_EQ(1, *new_set.begin());
    EXPECT_EQ(5, *new_set.end());
}

TEST(TestInit, withCopyArg) {
    int arr[] = {1, 2, 3, 5, 5, 5, 5};
    Set<int> new_set(arr, arr + 6);

    Set<int> another_set(new_set);

    EXPECT_EQ(4, another_set.size());
    EXPECT_EQ(1, *another_set.begin());
    EXPECT_EQ(5, *another_set.end());
}

TEST(TestInit, operatorEq) {
    int arr[] = {1, 2, 3, 5, 5, 5, 5};
    Set<int> new_set(arr, arr + 6);
    Set<int> another_set;

    another_set = new_set;

    EXPECT_EQ(4, another_set.size());
    EXPECT_EQ(1, *another_set.begin());
    EXPECT_EQ(5, *another_set.end());
}

TEST_F(OwnSet, begin) {
    EXPECT_EQ(-1, *new_set->begin());
}

TEST_F(OwnSet, end) {
    EXPECT_EQ(6, *new_set->end());
}

TEST_F(OwnSet, insert) {
    int start_own;
    int start_std;
    int end_own;
    int end_std;

    start_own = clock();
    new_set->insert(3);
    end_own = clock();

    start_std = clock();
    std_set->insert(3);
    end_std = clock();

    EXPECT_EQ(7, new_set->size());
    std::cerr << "Insert: " << end_own - start_own << "(Own) vs " << end_std - start_std << "(STD)" << std::endl;
}

TEST_F(OwnSet, erase) {
    int start_own;
    int start_std;
    int end_own;
    int end_std;

    start_own = clock();
    new_set->erase(5);
    end_own = clock();

    start_std = clock();
    std_set->erase(5);
    end_std = clock();

    EXPECT_EQ(5, new_set->size());
    std::cerr << "Erase: " << end_own - start_own << "(Own) vs " << end_std - start_std << "(STD)" << std::endl;
}

TEST_F(OwnSet, iteratorIncr) {
    EXPECT_EQ(0, *(++new_set->begin()));
}

TEST_F(OwnSet, iteratorDecr) {
    EXPECT_EQ(5, *(--new_set->end()));
}

TEST_F(OwnSet, size) {
    EXPECT_EQ(6, new_set->size());
}

TEST_F(OwnSet, empty) {
    EXPECT_EQ(false, new_set->empty());
}

TEST_F(OwnSet, find) {
    int start_own;
    int start_std;
    int end_own;
    int end_std;

    start_own = clock();
    auto it = new_set->find(4);
    end_own = clock();

    start_std = clock();
    std_set->find(4);
    end_std = clock();

    EXPECT_EQ(4, *it);
    std::cerr << "Find: " << end_own - start_own << "(Own) vs " << end_std - start_std << "(STD)" << std::endl;
}

TEST_F(OwnSet, lower_bound) {
    int start_own;
    int start_std;
    int end_own;
    int end_std;

    start_own = clock();
    auto it = new_set->lower_bound(3);
    end_own = clock();

    start_std = clock();
    std_set->lower_bound(3);
    end_std = clock();

    EXPECT_EQ(4, *it);
    std::cerr << "Lower bound: " << end_own - start_own << "(Own) vs " << end_std - start_std << "(STD)" << std::endl;
}


int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
