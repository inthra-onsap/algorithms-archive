cmake_minimum_required(VERSION 3.7)
project(algorithms_archive)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DUNIT_TESTS_)
add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES main.cc sorting/selection_sort/selection_sort.cc sorting/selection_sort/selection_sort.h sorting/selection_sort/selection_sort_test.cc tree/bst/bst_node.cc tree/bst/binary_search_tree.h tree/bst/binary_search_tree_test.cc tree/avl_tree/avl_tree.h tree/avl_tree/avl_node.cc tree/avl_tree/avl_tree_test.cc tree/splay_tree/splay_tree_node.cc tree/splay_tree/splay_tree.h tree/splay_tree/splay_tree_test.cc tree/rope_string/rope_string.h tree/rope_string/rope_node.cc tree/rope_string/rope_string_test.cc tree/rope_string/rope_string.cc tree/b_tree/b_tree.h tree/b_tree/b_tree_node.cc tree/b_tree/b_tree_test.cc tree/binary_heap/binary_heap.h tree/binary_heap/binary_heap_test.cc tree/leftist_heap/leftist_heap.h tree/leftist_heap/leftist_heap_node.cc tree/leftist_heap/leftist_heap_test.cc)
add_executable(algorithms_archive ${SOURCE_FILES})
target_link_libraries(algorithms_archive gtest gtest_main)

