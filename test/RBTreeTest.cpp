#include "../RBTree/RBTree.h"
#include <gtest/gtest.h>

TEST(RBTree, TestMinimum) {
    algs::RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);

    auto minValue = tree.min();

    auto expected = std::make_pair(1, 1);

    ASSERT_EQ(expected, minValue);
}

TEST(RBTree, TestMaximum) {
    algs::RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);

    auto maxValue = tree.max();
    auto expected = std::make_pair(2, 2);

    ASSERT_EQ(expected, maxValue);
}
