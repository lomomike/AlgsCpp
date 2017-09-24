cmake_minimum_required(VERSION 3.6)
project(AlgsCpp)

set(CMAKE_CXX_STANDARD 14)

set(RBTREE_SOURCES
        RBTree/RandomizedBST.h
        RBTree/RandomizedBSTVisualizer.h
        RBTree/RBTree.cpp
        RBTree/RBTree.h
        RBTree/RBTreeVisuzlizer.h)

set(SORT_SOURCES
        Sorting/Sorting.cpp)

set(BSTTREE_SOURCES
        BSTree/BST.h
        BSTree/BSTree.cpp)

set(PQUEUE_SOURCES
        PriorityQueue/BinaryHeapQueue.h
        PriorityQueue/PriorityQueue.cpp)


add_executable(RBTree ${RBTREE_SOURCES})
add_executable(Sorting ${SORT_SOURCES})
add_executable(BSTTree ${BSTTREE_SOURCES})
add_executable(PriorityQueue ${PQUEUE_SOURCES})