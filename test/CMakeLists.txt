include_directories(../RBTree)

add_executable(RBTReeTest RBTreeTest.cpp)
target_link_libraries(RBTReeTest gtest gtest_main)