cmake_minimum_required(VERSION 3.6)
project(collected)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} /usr/local/Cellar/GSL/master/include)

add_library(std_io STATIC Std_in.h Std_in.cpp Std_out.h Std_out.cpp)
add_library(std_random STATIC Std_in.h Std_in.cpp Std_out.h Std_out.cpp Std_random.h Std_random.cpp)
add_library(utility STATIC utility.h utility.cpp)

add_executable(accumulator_main accumulator_main.cpp Accumulator.h Std_in.h Std_in.cpp Std_out.h Std_out.cpp)
target_link_libraries(accumulator_main std_io)

set(ACYCLIC_LP_DEPS
        acyclic_lp_main.cpp
        Acyclic_lp.h
        Acyclic_lp.cpp
        Edge_weighted_digraph.h
        Edge_weighted_digraph.cpp
        Topological.h
        Topological.cpp
        Directed_edge.h
        Directed_edge.cpp
        Directed_cycle.h
        Directed_cycle.cpp
        Depth_first_order.h
        Depth_first_order.cpp
        Edge_weighted_digraph.h
        Edge_weighted_digraph.cpp
        Digraph.h
        Digraph.cpp
        Edge_weighted_directed_cycle.h
        Edge_weighted_directed_cycle.cpp
        )
add_executable(acyclic_lp_main ${ACYCLIC_LP_DEPS})
target_link_libraries(acyclic_lp_main std_random utility)

set(ACYCLIC_SP_DEPS
        acyclic_sp_main.cpp
        Acyclic_sp.h
        Acyclic_sp.cpp
        Edge_weighted_digraph.h
        Edge_weighted_digraph.cpp
        Topological.h
        Topological.cpp
        Directed_edge.h
        Directed_edge.cpp
        Directed_cycle.h
        Directed_cycle.cpp
        Depth_first_order.h
        Depth_first_order.cpp
        utility.h
        utility.cpp
        Edge_weighted_digraph.h
        Edge_weighted_digraph.cpp
        Digraph.h
        Digraph.cpp
        Edge_weighted_directed_cycle.h
        Edge_weighted_directed_cycle.cpp
        )
add_executable(acyclic_sp_main ${ACYCLIC_SP_DEPS})
target_link_libraries(acyclic_sp_main std_random utility)

set(ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_DEPS
        adj_matrix_edge_weighted_digraph_main.cpp
        Adj_matrix_edge_weighted_digraph.h
        Adj_matrix_edge_weighted_digraph.cpp
        Directed_edge.h
        Directed_edge.cpp
        )
add_executable(adj_matrix_edge_weighted_digraph_main ${ADJ_MATRIX_EDGE_WEIGHTED_DIGRAPH_DEPS})
target_link_libraries(adj_matrix_edge_weighted_digraph_main std_random)

add_executable(alphabet_main alphabet_main.cpp Alphabet.h Alphabet.cpp)

# TODO
add_executable(arbitrage_main arbitrage_main.cpp)
target_link_libraries(arbitrage_main std_io)

# TODO
add_executable(assignment_problem_main assignment_problem_main.cpp Assignment_problem.h Assignment_problem.cpp)
target_link_libraries(assignment_problem_main std_io)

add_executable(average_main average_main.cpp)

add_executable(avl_tree_symbol_table_main avl_tree_symbol_table_main.cpp AVL_tree_symbol_table.h)
target_link_libraries(avl_tree_symbol_table_main std_io std_random)

add_executable(b_tree_main b_tree_main.cpp B_tree.h)
target_link_libraries(b_tree_main std_io)

add_executable(bag_main bag_main.cpp Bag.h)
target_link_libraries(bag_main std_io)

add_executable(binary_insertion_sort_main binary_insertion_sort_main.cpp Binary_insertion_sort.h)
target_link_libraries(binary_insertion_sort_main std_io utility)

add_executable(binary_search_main binary_search_main.cpp Binary_search.h)
target_link_libraries(binary_search_main std_io)

add_executable(binary_search_symbol_table_main binary_search_symbol_table_main.cpp Binary_search_symbol_table.h)
target_link_libraries(binary_search_symbol_table_main std_io)

add_executable(binary_search_tree_main binary_search_tree_main.cpp Binary_search_tree.h)
target_link_libraries(binary_search_tree_main std_io)

add_executable(complex_main complex_main.cpp Complex.h Complex.cpp)
target_link_libraries(complex_main std_io)

add_executable(count_main count_main.cpp)
target_link_libraries(count_main std_io)

add_executable(counter_main counter_main.cpp Counter.h Counter.cpp)
target_link_libraries(counter_main std_random)

add_executable(depth_first_order_main depth_first_order_main.cpp Depth_first_order.h Depth_first_order.cpp)
# target_link_libraries(depth_first_order_main std_io)

add_executable(digraph_main digraph_main.cpp Digraph.h Digraph.cpp)
# target_link_libraries(digraph_main std_io)

add_executable(directed_cycle_main directed_cycle_main.cpp Directed_cycle.h Directed_cycle.cpp)
# target_link_libraries(directed_cycle_main std_io)

add_executable(directed_edge_main directed_edge_main.cpp Directed_edge.h Directed_edge.cpp)
target_link_libraries(directed_edge_main std_io)

set(EDGE_WEIGHTED_DIGRAPH_DEPS
        edge_weighted_digraph_main.cpp
        Edge_weighted_digraph.cpp
        Edge_weighted_digraph.h
        Directed_edge.h
        Directed_edge.cpp
        )
add_executable(edge_weighted_digraph_main ${EDGE_WEIGHTED_DIGRAPH_DEPS})
target_link_libraries(edge_weighted_digraph_main std_random utility)

add_executable(edge_weighted_directed_cycle_main edge_weighted_directed_cycle_main.cpp Edge_weighted_directed_cycle.h Edge_weighted_directed_cycle.cpp)
# target_link_libraries(edge_weighted_directed_cycle_main std_io)

add_executable(graph_main graph_main.cpp Graph.h Graph.cpp)
# target_link_libraries(graph_main std_io)

add_executable(heap_sort_main heap_sort_main.cpp Heap_sort.h)
target_link_libraries(heap_sort_main std_io utility)

add_executable(insertion_sort_main insertion_sort_main.cpp Insertion_sort.h Insertion_sort.cpp)
target_link_libraries(insertion_sort_main std_io utility)

add_executable(insertion_sort_x_main insertion_sort_x_main.cpp Insertion_sort_x.h)
target_link_libraries(insertion_sort_x_main std_io utility)

add_executable(knuth_morris_pratt_main knuth_morris_pratt_main.cpp Knuth_morris_pratt.h Knuth_morris_pratt.cpp)
target_link_libraries(knuth_morris_pratt_main std_io)

add_executable(knuth_shuffle_main knuth_shuffle_main.cpp Knuth_shuffle.h)
target_link_libraries(knuth_shuffle_main std_random utility)

add_executable(linear_probing_hash_symbol_table_main linear_probing_hash_symbol_table_main.cpp Linear_probing_hash_symbol_table.h)
target_link_libraries(linear_probing_hash_symbol_table_main std_io)

add_executable(lsd_radix_sort_main lsd_radix_sort_main.cpp LSD_radix_sort.h)
target_link_libraries(lsd_radix_sort_main std_io utility)

add_executable(mergesort_main mergesort_main.cpp Mergesort.h)
target_link_libraries(mergesort_main std_io utility)

add_executable(mergesort_bu_main mergesort_bu_main.cpp Mergesort_bu.h)
target_link_libraries(mergesort_bu_main std_io utility)

add_executable(mergesort_x_main mergesort_x_main.cpp Mergesort_x.h)
target_link_libraries(mergesort_x_main std_io utility)

add_executable(msd_radix_sort_main msd_radix_sort_main.cpp MSD_radix_sort.h MSD_radix_sort.cpp)
target_link_libraries(msd_radix_sort_main std_io utility)

add_executable(queue_main queue_main.cpp Queue.h)
target_link_libraries(queue_main std_io)

add_executable(quicksort_main quicksort_main.cpp Quicksort.h)
target_link_libraries(quicksort_main std_io utility)

add_executable(quicksort_3_string_main quicksort_3_string_main.cpp Quicksort_3_string.h Quicksort_3_string.cpp)
target_link_libraries(quicksort_3_string_main std_io utility)

add_executable(quicksort_3_way_main quicksort_3_way_main.cpp Quicksort_3_way.h)
target_link_libraries(quicksort_3_way_main std_io utility)

add_executable(quicksort_x_main quicksort_x_main.cpp Quicksort_x.h)
target_link_libraries(quicksort_x_main std_io utility)

add_executable(red_black_bst_main red_black_bst_main.cpp Red_black_bst.h Red_black_bst.cpp)
target_link_libraries(red_black_bst_main std_io)

add_executable(selection_sort_main selection_sort_main.cpp Selection_sort.h)
target_link_libraries(selection_sort_main std_io utility)

add_executable(shellsort_main shellsort_main.cpp Shellsort.h)
target_link_libraries(shellsort_main std_io utility)

add_executable(stack_main stack_main.cpp Stack.h)
target_link_libraries(stack_main std_io)

add_executable(std_in_main std_in_main.cpp)
target_link_libraries(std_in_main std_io)

add_executable(std_out_main std_out_main.cpp)
target_link_libraries(std_out_main std_io)

add_executable(std_random_main std_random_main.cpp)
target_link_libraries(std_random_main std_random utility)

add_executable(set_main set_main.cpp Set.h)
target_link_libraries(set_main std_io)

add_executable(topological_main topological_main.cpp Topological.h Topological.cpp)
target_link_libraries(topological_main std_io)

add_executable(union_find_main union_find_main.cpp Union_find.h Union_find.cpp)
target_link_libraries(union_find_main std_io)

add_executable(weighted_quick_union_uf_main weighted_quick_union_uf_main.cpp Weighted_quick_union_uf.h Weighted_quick_union_uf.cpp)
target_link_libraries(weighted_quick_union_uf_main std_io)

add_executable(white_filter_main white_filter_main.cpp Set.h)
target_link_libraries(white_filter_main std_io)

add_executable(whitelist_main whitelist_main.cpp Static_set_of_ints.h Static_set_of_ints.cpp)
target_link_libraries(whitelist_main std_io utility)