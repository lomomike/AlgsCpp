include_directories(../RBTree)

SET (LINK_FLAGS "-static-libgcc -static-libstdc++")

SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${LINK_FLAGS}")

add_executable(RBTReeTest RBTreeTest.cpp)
target_link_libraries(RBTReeTest gtest gtest_main)

add_test(RBTreeTest RBTReeTest)