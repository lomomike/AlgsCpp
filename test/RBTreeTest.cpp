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

TEST(RBTree, TestSuccessor) {
    algs::RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);

    auto successor = tree.successor(1);
    auto expected = 2;

    ASSERT_EQ(expected, successor);
}

TEST(RBTree, TestPredecessor) {
    algs::RBTree<int, int> tree;
    tree.insert(1, 1);
    tree.insert(2, 2);

    auto successor = tree.predecessor(2);
    auto expected = 1;

    ASSERT_EQ(expected, successor);
}
