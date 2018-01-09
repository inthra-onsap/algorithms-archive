cmake_minimum_required(VERSION 3.7)
project(algorithms_archive)

set(CMAKE_CXX_STANDARD 14)
add_definitions(-DUNIT_TESTS_)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

set(SOURCE_FILES
        main.cc
        sorting/selection_sort/selection_sort_test.cc
        tree/bst/bst_node.cc
        tree/bst/binary_search_tree.h
        tree/bst/binary_search_tree_test.cc
        tree/avl_tree/avl_tree.h
        tree/avl_tree/avl_node.cc
        tree/avl_tree/avl_tree_test.cc
        tree/splay_tree/splay_tree_node.cc
        tree/splay_tree/splay_tree.h
        tree/splay_tree/splay_tree_test.cc
        string/rope_string/rope_string.h
        string/rope_string/rope_node.cc
        string/rope_string/rope_string_test.cc
        string/rope_string/rope_string.cc
        tree/b_tree/b_tree.h
        tree/b_tree/b_tree_node.cc
        tree/b_tree/b_tree_test.cc
        tree/binary_heap/binary_heap.h
        tree/binary_heap/binary_heap_test.cc
        tree/leftist_heap/leftist_heap.h
        tree/leftist_heap/leftist_heap_node.cc
        tree/leftist_heap/leftist_heap_test.cc
        tree/binomial_tree/binomial_tree.h
        tree/binomial_tree/binomial_heap_node.cc
        tree/binomial_tree/binomial_tree_test.cc
        sorting/insertion_sort/insertion_sort_test.cc
        sorting/insertion_sort/insertion_sort.h
        sorting/selection_sort/selection_sort.h
        sorting/merge_sort/merge_sort.h
        sorting/merge_sort/merge_sort_test.cc
        sorting/quick_sort/quick_sort.h
        sorting/quick_sort/quick_sort_test.cc
        sorting/bucket_sort/bucket_sort.h
        sorting/bucket_sort/bucket_sort_test.cc
        sorting/radix_sort/radix_sort.h
        sorting/radix_sort/radix_sort_test.cc
        sorting/bubble_sort/bubble_sort.h
        sorting/bubble_sort/bubble_sort_test.cc
        sorting/shell_sort/shell_sort.h
        sorting/shell_sort/shell_sort_test.cc
        sorting/heap_sort/heap_sort.h
        sorting/heap_sort/heap_sort_test.cc
        disjoint_sets/disjoint_sets/disjoint_sets.h
        disjoint_sets/disjoint_sets/disjoint_sets_test.cc
        disjoint_sets/disjoint_sets/disjoint_sets.cc
        graphs/topological_sort/graph_topological_sort.cc
        graphs/topological_sort/graph_topological_sort.h
        graphs/topological_sort/graph_topological_sort_test.cc
        memory_management/lru_cache/lru_cache.h
        memory_management/lru_cache/lru_cache_test.cc
        graphs/dijkstra/dijkstra.h
        graphs/dijkstra/dijkstra_test.cc
        graphs/dijkstra/dijkstra.cc
        graphs/utility/graph_min_heap.h
        graphs/bellman_ford/bellman_ford.cc
        graphs/bellman_ford/bellman_ford.h
        graphs/bellman_ford/bellman_ford_test.cc
        graphs/kruskal/kruskal.cc
        graphs/kruskal/kruskal.h
        graphs/kruskal/kruskal_test.cc
        graphs/prim/prim.cc
        graphs/prim/prim.h
        graphs/prim/prim_test.cc
        graphs/bidirectional_dijkstra/bidirectional_dijkstra.cc
        graphs/bidirectional_dijkstra/bidirectional_dijkstra.h
        graphs/bidirectional_dijkstra/bidirectional_dijkstra_test.cc
        graphs/ford_fulkerson/ford_fulkerson.cc
        graphs/ford_fulkerson/ford_fulkerson.h
        graphs/ford_fulkerson/ford_fulkerson_test.cc
        tree/topdown_splay_tree/topdown_splay_tree.h
        tree/topdown_splay_tree/splay_tree_node.cc
        tree/topdown_splay_tree/topdown_splay_tree_test.cc
        tree/redblack_tree/redblack_node.cc
        tree/redblack_tree/redblack_tree.h
        tree/redblack_tree/redblack_tree_test.cc
        tree/treap/treap_node.cc tree/treap/treap.h
        tree/treap/treap_test.cc
        string/suffix_array/suffix_array.cc
        string/suffix_array/suffix_array.h
        string/suffix_array/suffix_array_test.cc
        string/knuth_morris_patt/knuth_morris_patt.cc
        string/knuth_morris_patt/knuth_morris_patt.h
        string/knuth_morris_patt/knuth_morris_patt_test.cc
        graphs/strongly_connected_component/graph_strongly_connected_component.cc
        graphs/strongly_connected_component/graph_strongly_connected_component.h
        graphs/strongly_connected_component/graph_strongly_connected_component_test.cc
        tree/segment_tree/segment_tree.h tree/segment_tree/segment_tree_test.cc
        tree/binary_index_tree/binary_indexed_tree.h
        tree/binary_index_tree/binary_indexed_tree_test.cc
        tree/lca/lca.h tree/lca/lca_test.cc tree/lca/lca.cc
        string/trie/trie.cc string/trie/trie.h
        string/trie/trie_test.cc string/trie/trie_node.cc
        string/suffix_tree/suffix_tree.cc
        string/suffix_tree/suffix_tree.h
        string/suffix_tree/suffix_tree_test.cc
        string/rabin_karp/rabin_karp.cc
        string/rabin_karp/rabin_karp.h
        string/rabin_karp/rabin_karp_test.cc
        string/finite_automata/finite_automata.cc
        string/finite_automata/finite_automata.h
        string/finite_automata/finite_automata_test.cc
        string/radix_tree/radix_tree.cc
        string/radix_tree/radix_tree.h
        string/radix_tree/radix_tree_test.cc
        string/radix_tree/trie_node.cc
        string/suffix_tree/suffix_node.cc
        order_statistic/selection/selection.h
        order_statistic/selection/selection_test.cc string/binary_radix_tree/binary_radix_tree.cc string/binary_radix_tree/binary_radix_tree.h string/binary_radix_tree/binary_redix_tree_test.cc)

add_executable(algorithms_archive ${SOURCE_FILES})
target_link_libraries(algorithms_archive gtest gtest_main)