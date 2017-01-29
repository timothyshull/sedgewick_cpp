cmake_minimum_required(VERSION 3.6)
project(collected)

set(CMAKE_CXX_STANDARD 14)

# for Qt
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(QT_PATH "/usr/local/opt/qt5")

set(QT_LIB_DIR ${QT_PATH}/lib/cmake)

set(Qt5Core_DIR "${QT_LIB_DIR}/Qt5Core")
set(Qt5Gui_DIR "${QT_LIB_DIR}/Qt5Gui")
set(Qt5Multimedia_DIR "${QT_LIB_DIR}/Qt5Multimedia")
set(Qt5Widgets_DIR "${QT_LIB_DIR}/Qt5Widgets")

set(QT_LIBRARIES
        Qt5::Core
        Qt5::Gui
        Qt5::Multimedia
        Qt5::Widgets)

set(QT_LIBRARIES_REQUIRED
        Qt5Core
        Qt5Gui
        Qt5Multimedia
        Qt5Widgets)

foreach (QT_LIBRARIES_REQUIRED ${QT_LIBRARIES_REQUIRED})
    find_package(${QT_LIBRARIES_REQUIRED} REQUIRED)
endforeach ()

#find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} /usr/local/Cellar/GSL/master/include)
# for Timsort _tmp file
include_directories(/usr/local/var/pyenv/versions/3.6.0/Python.framework/Versions/3.6/include/python3.6m)

add_library(std_io STATIC Std_in.h Std_in.cpp Std_out.h Std_out.cpp)
add_library(std_random STATIC Std_random.h Std_random.cpp)
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
target_link_libraries(acyclic_lp_main std_random utility ${Boost_LIBRARIES})

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
target_link_libraries(acyclic_sp_main std_random utility ${Boost_LIBRARIES})

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
target_link_libraries(binary_insertion_sort_main std_io utility ${Boost_LIBRARIES})

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
target_link_libraries(edge_weighted_digraph_main std_random utility ${Boost_LIBRARIES})

add_executable(edge_weighted_directed_cycle_main edge_weighted_directed_cycle_main.cpp Edge_weighted_directed_cycle.h Edge_weighted_directed_cycle.cpp)
# target_link_libraries(edge_weighted_directed_cycle_main std_io)

add_executable(graph_main graph_main.cpp Graph.h Graph.cpp)
# target_link_libraries(graph_main std_io)

add_executable(heap_sort_main heap_sort_main.cpp Heap_sort.h)
target_link_libraries(heap_sort_main std_io utility ${Boost_LIBRARIES})

add_executable(insertion_sort_main insertion_sort_main.cpp Insertion_sort.h Insertion_sort.cpp)
target_link_libraries(insertion_sort_main std_io utility ${Boost_LIBRARIES})

add_executable(insertion_sort_x_main insertion_sort_x_main.cpp Insertion_sort_x.h)
target_link_libraries(insertion_sort_x_main std_io utility ${Boost_LIBRARIES})

add_executable(knuth_morris_pratt_main knuth_morris_pratt_main.cpp Knuth_morris_pratt.h Knuth_morris_pratt.cpp)
target_link_libraries(knuth_morris_pratt_main std_io)

add_executable(knuth_shuffle_main knuth_shuffle_main.cpp Knuth_shuffle.h)
target_link_libraries(knuth_shuffle_main std_random utility ${Boost_LIBRARIES})

add_executable(linear_probing_hash_symbol_table_main linear_probing_hash_symbol_table_main.cpp Linear_probing_hash_symbol_table.h)
target_link_libraries(linear_probing_hash_symbol_table_main std_io)

add_executable(lsd_radix_sort_main lsd_radix_sort_main.cpp LSD_radix_sort.h)
target_link_libraries(lsd_radix_sort_main std_io utility ${Boost_LIBRARIES})

add_executable(max_pq_main max_pq_main.cpp Max_pq.h)
target_link_libraries(max_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(mergesort_main mergesort_main.cpp Mergesort.h)
target_link_libraries(mergesort_main std_io utility ${Boost_LIBRARIES})

add_executable(mergesort_bu_main mergesort_bu_main.cpp Mergesort_bu.h)
target_link_libraries(mergesort_bu_main std_io utility ${Boost_LIBRARIES})

add_executable(mergesort_x_main mergesort_x_main.cpp Mergesort_x.h)
target_link_libraries(mergesort_x_main std_io utility ${Boost_LIBRARIES})

add_executable(min_pq_main min_pq_main.cpp Min_pq.h)
target_link_libraries(min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(msd_radix_sort_main msd_radix_sort_main.cpp MSD_radix_sort.h MSD_radix_sort.cpp)
target_link_libraries(msd_radix_sort_main std_io utility ${Boost_LIBRARIES})

add_executable(queue_main queue_main.cpp Queue.h)
target_link_libraries(queue_main std_io)

add_executable(quicksort_main quicksort_main.cpp Quicksort.h)
target_link_libraries(quicksort_main std_io utility ${Boost_LIBRARIES})

add_executable(quicksort_3_string_main quicksort_3_string_main.cpp Quicksort_3_string.h Quicksort_3_string.cpp)
target_link_libraries(quicksort_3_string_main std_io utility ${Boost_LIBRARIES})

add_executable(quicksort_3_way_main quicksort_3_way_main.cpp Quicksort_3_way.h)
target_link_libraries(quicksort_3_way_main std_io utility ${Boost_LIBRARIES})

add_executable(quicksort_x_main quicksort_x_main.cpp Quicksort_x.h)
target_link_libraries(quicksort_x_main std_io utility ${Boost_LIBRARIES})

add_executable(red_black_bst_main red_black_bst_main.cpp Red_black_bst.h Red_black_bst.cpp)
target_link_libraries(red_black_bst_main std_io)

add_executable(selection_sort_main selection_sort_main.cpp Selection_sort.h)
target_link_libraries(selection_sort_main std_io utility ${Boost_LIBRARIES})

add_executable(set_main set_main.cpp Set.h)
target_link_libraries(set_main std_io utility ${Boost_LIBRARIES})

add_executable(shellsort_main shellsort_main.cpp Shellsort.h)
target_link_libraries(shellsort_main std_io utility ${Boost_LIBRARIES})

add_executable(stack_main stack_main.cpp Stack.h)
target_link_libraries(stack_main std_io)

add_executable(std_in_main std_in_main.cpp)
target_link_libraries(std_in_main std_io)

add_executable(std_out_main std_out_main.cpp)
target_link_libraries(std_out_main std_io)

add_executable(std_random_main std_random_main.cpp)
target_link_libraries(std_random_main std_random utility ${Boost_LIBRARIES})

# TODO
add_executable(timsort_main timsort_main.cpp Timsort.h Timsort_tmp.c)
target_link_libraries(timsort_main std_io utility ${Boost_LIBRARIES})

add_executable(timsort_py Timsort_py.h Timsort_py.cpp)

add_executable(topological_main topological_main.cpp Topological.h Topological.cpp)
target_link_libraries(topological_main std_io)

add_executable(union_find_main union_find_main.cpp Union_find.h Union_find.cpp)
target_link_libraries(union_find_main std_io)

add_executable(weighted_quick_union_uf_main weighted_quick_union_uf_main.cpp Weighted_quick_union_uf.h Weighted_quick_union_uf.cpp)
target_link_libraries(weighted_quick_union_uf_main std_io)

add_executable(white_filter_main white_filter_main.cpp Set.h)
target_link_libraries(white_filter_main std_io)

add_executable(whitelist_main whitelist_main.cpp Static_set_of_ints.h Static_set_of_ints.cpp)
target_link_libraries(whitelist_main std_io utility ${Boost_LIBRARIES})







add_executable(bellman_ford_sp_main bellman_ford_sp_main.cpp Bellman_ford_sp.cpp Bellman_ford_sp.h)
target_link_libraries(bellman_ford_sp_main std_io utility ${Boost_LIBRARIES})

add_executable(binary_dump_main binary_dump_main.cpp)
target_link_libraries(binary_dump_main std_io utility ${Boost_LIBRARIES})

add_executable(binary_in_main binary_in_main.cpp Binary_in.cpp Binary_in.h)
target_link_libraries(binary_in_main std_io utility ${Boost_LIBRARIES})

add_executable(binary_out_main binary_out_main.cpp Binary_out.cpp Binary_out.h)
target_link_libraries(binary_out_main std_io utility ${Boost_LIBRARIES})

add_executable(binary_std_in_main binary_std_in_main.cpp Binary_std_in.cpp Binary_std_in.h) # TODO: 3rd round)
target_link_libraries(binary_std_in_main std_io utility ${Boost_LIBRARIES})

add_executable(binary_std_out_main binary_std_out_main.cpp Binary_std_out.cpp Binary_std_out.h) # TODO: 3rd round)
target_link_libraries(binary_std_out_main std_io utility ${Boost_LIBRARIES})

add_executable(binomial_min_priority_queue_main binomial_min_pq_main.cpp Binomial_min_pq.h)
target_link_libraries(binomial_min_priority_queue_main std_io utility ${Boost_LIBRARIES})

add_executable(bipartite_main bipartite_main.cpp Bipartite.cpp Bipartite.h)
target_link_libraries(bipartite_main std_io utility ${Boost_LIBRARIES})

add_executable(bipartite_x_main bipartite_x_main.cpp Bipartite_x.cpp Bipartite_x.h)
target_link_libraries(bipartite_x_main std_io utility ${Boost_LIBRARIES})

add_executable(black_filter_main black_filter_main.cpp)
target_link_libraries(black_filter_main std_io utility ${Boost_LIBRARIES})

add_executable(boruvka_mst_main boruvka_mst_main.cpp Boruvka_mst.cpp Boruvka_mst.h)
target_link_libraries(boruvka_mst_main std_io utility ${Boost_LIBRARIES})

add_executable(boyer_moore_main boyer_moore_main.cpp Boyer_moore.cpp Boyer_moore.h)
target_link_libraries(boyer_moore_main std_io utility ${Boost_LIBRARIES})

add_executable(breadth_first_directed_paths_main breadth_first_directed_paths_main.cpp Breadth_first_directed_paths.cpp Breadth_first_directed_paths.h)
target_link_libraries(breadth_first_directed_paths_main std_io utility ${Boost_LIBRARIES})

add_executable(breadth_first_paths_main breadth_first_paths_main.cpp Breadth_first_paths.cpp Breadth_first_paths.h)
target_link_libraries(breadth_first_paths_main std_io utility ${Boost_LIBRARIES})

add_executable(cat_main cat_main.cpp)
target_link_libraries(cat_main std_io utility ${Boost_LIBRARIES})

add_executable(closest_pair_main closest_pair_main.cpp Closest_pair.cpp Closest_pair.h)
target_link_libraries(closest_pair_main std_io utility ${Boost_LIBRARIES})

add_executable(collision_system_main collision_system_main.cpp Collision_system.cpp Collision_system.h)
target_link_libraries(collision_system_main std_io utility ${Boost_LIBRARIES})

add_executable(connected_component_main connected_component_main.cpp Connected_component.cpp Connected_component.h)
target_link_libraries(connected_component_main std_io utility ${Boost_LIBRARIES})

add_executable(cpm_main cpm_main.cpp)
target_link_libraries(cpm_main std_io utility ${Boost_LIBRARIES})

add_executable(cycle_main cycle_main.cpp Cycle.cpp Cycle.h)
target_link_libraries(cycle_main std_io utility ${Boost_LIBRARIES})

add_executable(date_main date_main.cpp Date.cpp Date.h)
target_link_libraries(date_main std_io utility ${Boost_LIBRARIES})

add_executable(de_dup_main de_dup_main.cpp)
target_link_libraries(de_dup_main std_io utility ${Boost_LIBRARIES})

add_executable(degrees_of_separation_main degrees_of_separation_main.cpp)
target_link_libraries(degrees_of_separation_main std_io utility ${Boost_LIBRARIES})

add_executable(depth_first_directed_paths_main depth_first_directed_paths_main.cpp Depth_first_directed_paths.cpp Depth_first_directed_paths.h)
target_link_libraries(depth_first_directed_paths_main std_io utility ${Boost_LIBRARIES})

add_executable(depth_first_paths_main depth_first_paths_main.cpp Depth_first_paths.cpp Depth_first_paths.h)
target_link_libraries(depth_first_paths_main std_io utility ${Boost_LIBRARIES})

add_executable(depth_first_search_main depth_first_search_main.cpp Depth_first_search.cpp Depth_first_search.h)
target_link_libraries(depth_first_search_main std_io utility ${Boost_LIBRARIES})

add_executable(digraph_generator_main digraph_generator_main.cpp Digraph_generator.cpp Digraph_generator.h Digraph.h Digraph.cpp)
target_link_libraries(digraph_generator_main std_io std_random utility ${Boost_LIBRARIES})

add_executable(dijkstra_all_pairs_sp_main dijkstra_all_pairs_sp_main.cpp Dijkstra_all_pairs_sp.cpp Dijkstra_all_pairs_sp.h)
target_link_libraries(dijkstra_all_pairs_sp_main std_io utility ${Boost_LIBRARIES})

add_executable(dijkstra_sp_main dijkstra_sp_main.cpp Dijkstra_sp.cpp Dijkstra_sp.h)
target_link_libraries(dijkstra_sp_main std_io utility ${Boost_LIBRARIES})

add_executable(dijkstra_undirected_sp_main dijkstra_undirected_sp_main.cpp Dijkstra_undirected_sp.cpp Dijkstra_undirected_sp.h)
target_link_libraries(dijkstra_undirected_sp_main std_io utility ${Boost_LIBRARIES})

add_executable(directed_cycle_x_main directed_cycle_x_main.cpp Directed_cycle_x.cpp Directed_cycle_x.h)
target_link_libraries(directed_cycle_x_main std_io utility ${Boost_LIBRARIES})

add_executable(directed_dfs_main directed_dfs_main.cpp Directed_dfs.cpp Directed_dfs.h)
target_link_libraries(directed_dfs_main std_io utility ${Boost_LIBRARIES})

add_executable(directed_eulerian_cycle_main directed_eulerian_cycle_main.cpp Directed_eulerian_cycle.cpp Directed_eulerian_cycle.h)
target_link_libraries(directed_eulerian_cycle_main std_io utility ${Boost_LIBRARIES})

add_executable(directed_eulerian_path_main directed_eulerian_path_main.cpp Directed_eulerian_path.cpp Directed_eulerian_path.h)
target_link_libraries(directed_eulerian_path_main std_io utility ${Boost_LIBRARIES})

add_executable(doubling_ratio_main doubling_ratio_main.cpp Doubling_ratio.cpp Doubling_ratio.h Stopwatch.h Stopwatch.cpp Three_sum.h Three_sum.cpp)
target_link_libraries(doubling_ratio_main std_io std_random utility ${Boost_LIBRARIES})

add_executable(doubling_test_main doubling_test_main.cpp Doubling_test.cpp Doubling_test.h)
target_link_libraries(doubling_test_main std_io utility ${Boost_LIBRARIES})

add_executable(draw_main draw_main.cpp Draw.cpp Draw.h Draw_listener.h) # TODO: implement using Qt)
target_link_libraries(draw_main std_io utility ${Boost_LIBRARIES})

add_executable(edge_main edge_main.cpp Edge.cpp Edge.h)
target_link_libraries(edge_main std_io utility ${Boost_LIBRARIES})

add_executable(edge_weighted_graph_main edge_weighted_graph_main.cpp Edge_weighted_graph.cpp Edge_weighted_graph.h)
target_link_libraries(edge_weighted_graph_main std_io utility ${Boost_LIBRARIES})

add_executable(eulerian_cycle_main eulerian_cycle_main.cpp Eulerian_cycle.cpp Eulerian_cycle.h)
target_link_libraries(eulerian_cycle_main std_io utility ${Boost_LIBRARIES})

add_executable(eulerian_path_main eulerian_path_main.cpp Eulerian_path.cpp Eulerian_path.h)
target_link_libraries(eulerian_path_main std_io utility ${Boost_LIBRARIES})

add_executable(fenwick_tree_main fenwick_tree_main.cpp Fenwick_tree.cpp Fenwick_tree.h)
target_link_libraries(fenwick_tree_main std_io utility ${Boost_LIBRARIES})

add_executable(fft_main fft_main.cpp FFT.cpp FFT.h)
target_link_libraries(fft_main std_io utility ${Boost_LIBRARIES})

add_executable(fibonacci_min_pq_main fibonacci_min_pq_main.cpp Fibonacci_min_pq.h)
target_link_libraries(fibonacci_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(file_index_main file_index_main.cpp)
target_link_libraries(file_index_main std_io utility ${Boost_LIBRARIES})

add_executable(flow_edge_main flow_edge_main.cpp Flow_edge.cpp Flow_edge.h)
target_link_libraries(flow_edge_main std_io utility ${Boost_LIBRARIES})

add_executable(flow_network_main flow_network_main.cpp Flow_network.cpp Flow_network.h)
target_link_libraries(flow_network_main std_io utility ${Boost_LIBRARIES})

add_executable(floyd_warshall_main floyd_warshall_main.cpp Floyd_warshall.cpp Floyd_warshall.h)
target_link_libraries(floyd_warshall_main std_io utility ${Boost_LIBRARIES})

add_executable(ford_fulkerson_main ford_fulkerson_main.cpp Ford_fulkerson.cpp Ford_fulkerson.h)
target_link_libraries(ford_fulkerson_main std_io utility ${Boost_LIBRARIES})

add_executable(frequency_counter_main frequency_counter_main.cpp)
target_link_libraries(frequency_counter_main std_io utility ${Boost_LIBRARIES})

add_executable(furthest_pair_main furthest_pair_main.cpp Furthest_pair.cpp Furthest_pair.h)
target_link_libraries(furthest_pair_main std_io utility ${Boost_LIBRARIES})

add_executable(gabow_scc_main gabow_scc_main.cpp Gabow_scc.cpp Gabow_scc.h)
target_link_libraries(gabow_scc_main std_io utility ${Boost_LIBRARIES})

add_executable(gauss_jordan_elimination_main gauss_jordan_elimination_main.cpp Gauss_jordan_elimination.cpp Gauss_jordan_elimination.h)
target_link_libraries(gauss_jordan_elimination_main std_io utility ${Boost_LIBRARIES})

add_executable(gaussian_elimination_main gaussian_elimination_main.cpp Gaussian_elimination.cpp Gaussian_elimination.h)
target_link_libraries(gaussian_elimination_main std_io utility ${Boost_LIBRARIES})

add_executable(genome_main genome_main.cpp Genome.cpp Genome.h)
target_link_libraries(genome_main std_io utility ${Boost_LIBRARIES})

add_executable(graham_scan_main graham_scan_main.cpp Graham_scan.cpp Graham_scan.h)
target_link_libraries(graham_scan_main std_io utility ${Boost_LIBRARIES})

add_executable(graph_generator_main graph_generator_main.cpp Graph_generator.cpp Graph_generator.h)
target_link_libraries(graph_generator_main std_io utility ${Boost_LIBRARIES})

add_executable(grep_main grep_main.cpp)
target_link_libraries(grep_main std_io utility ${Boost_LIBRARIES})

add_executable(hex_dump_main hex_dump_main.cpp)
target_link_libraries(hex_dump_main std_io utility ${Boost_LIBRARIES})

add_executable(hopcroft_karp_main hopcroft_karp_main.cpp Hopcroft_karp.cpp Hopcroft_karp.h)
target_link_libraries(hopcroft_karp_main std_io utility ${Boost_LIBRARIES})

add_executable(huffman_main huffman_main.cpp Huffman.cpp Huffman.h)
target_link_libraries(huffman_main std_io utility ${Boost_LIBRARIES})

add_executable(in_main in_main.cpp In.cpp In.h) # TODO
target_link_libraries(in_main std_io utility ${Boost_LIBRARIES})

# TODO: 3rd Round
add_executable(index_binomial_min_pq_main index_binomial_min_pq_main.cpp Index_binomial_min_pq.h)
target_link_libraries(index_binomial_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(index_fibonacci_min_pq_main index_fibonacci_min_pq_main.cpp Index_fibonacci_min_pq.cpp Index_fibonacci_min_pq.h)
target_link_libraries(index_fibonacci_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(index_max_pq_main index_max_pq_main.cpp Index_max_pq.h)
target_link_libraries(index_max_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(index_min_pq_main index_min_pq_main.cpp Index_min_pq.h)
target_link_libraries(index_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(index_multiway_min_pq_main index_multiway_min_pq_main.cpp Index_multiway_min_pq.cpp Index_multiway_min_pq.h)
target_link_libraries(index_multiway_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(interval_1d_main interval_1d_main.cpp Interval_1d.cpp Interval_1d.h)
target_link_libraries(interval_1d_main std_io utility ${Boost_LIBRARIES})

add_executable(interval_2d_main interval_2d_main.cpp Interval_2d.cpp Interval_2d.h)
target_link_libraries(interval_2d_main std_io utility ${Boost_LIBRARIES})

add_executable(kosaraju_sharir_scc_main kosaraju_sharir_scc_main.cpp Kosaraju_sharir_scc.cpp Kosaraju_sharir_scc.h)
target_link_libraries(kosaraju_sharir_scc_main std_io utility ${Boost_LIBRARIES})

add_executable(kruskal_mst_main kruskal_mst_main.cpp Kruskal_mst.cpp Kruskal_mst.h)
target_link_libraries(kruskal_mst_main std_io utility ${Boost_LIBRARIES})

add_executable(kwik_main kwik_main.cpp)
target_link_libraries(kwik_main std_io utility ${Boost_LIBRARIES})

add_executable(lazy_prim_mst_main lazy_prim_mst_main.cpp Lazy_prim_mst.cpp Lazy_prim_mst.h)
target_link_libraries(lazy_prim_mst_main std_io utility ${Boost_LIBRARIES})

add_executable(linear_programming_main linear_programming_main.cpp Linear_programming.cpp Linear_programming.h)
target_link_libraries(linear_programming_main std_io utility ${Boost_LIBRARIES})

add_executable(linear_regression_main linear_regression_main.cpp Linear_regression.cpp Linear_regression.h)
target_link_libraries(linear_regression_main std_io utility ${Boost_LIBRARIES})

add_executable(linked_bag_main linked_bag_main.cpp Linked_bag.cpp Linked_bag.h) # TODO)
target_link_libraries(linked_bag_main std_io utility ${Boost_LIBRARIES})

add_executable(linked_queue_main linked_queue_main.cpp Linked_queue.cpp Linked_queue.h) # TODO)
target_link_libraries(linked_queue_main std_io utility ${Boost_LIBRARIES})

add_executable(linked_stack_main linked_stack_main.cpp Linked_stack.cpp Linked_stack.h) # TODO)
target_link_libraries(linked_stack_main std_io utility ${Boost_LIBRARIES})

add_executable(longest_common_substring_main longest_common_substring_main.cpp Longest_common_substring.cpp Longest_common_substring.h)
target_link_libraries(longest_common_substring_main std_io utility ${Boost_LIBRARIES})

add_executable(longest_repeated_substring_main longest_repeated_substring_main.cpp Longest_repeated_substring.cpp Longest_repeated_substring.h)
target_link_libraries(longest_repeated_substring_main std_io utility ${Boost_LIBRARIES})

add_executable(lookup_csv_main lookup_csv_main.cpp)
target_link_libraries(lookup_csv_main std_io utility ${Boost_LIBRARIES})

add_executable(lookup_index_main lookup_index_main.cpp)
target_link_libraries(lookup_index_main std_io utility ${Boost_LIBRARIES})

add_executable(lzw_compression_main lzw_compression_main.cpp LZW_compression.cpp LZW_compression.h)
target_link_libraries(lzw_compression_main std_io utility ${Boost_LIBRARIES})

add_executable(multiway_merge_main multiway_merge_main.cpp Multiway_merge.cpp Multiway_merge.h)
target_link_libraries(multiway_merge_main std_io utility ${Boost_LIBRARIES})

add_executable(multiway_min_pq_main multiway_min_pq_main.cpp Multiway_min_pq.cpp Multiway_min_pq.h)
target_link_libraries(multiway_min_pq_main std_io utility ${Boost_LIBRARIES})

add_executable(nfa_main nfa_main.cpp NFA.cpp NFA.h)
target_link_libraries(nfa_main std_io utility ${Boost_LIBRARIES})

add_executable(nonrecursive_dfs_main nonrecursive_dfs_main.cpp Nonrecursive_dfs.cpp Nonrecursive_dfs.h)
target_link_libraries(nonrecursive_dfs_main std_io utility ${Boost_LIBRARIES})

add_executable(nonrecursive_directed_dfs_main nonrecursive_directed_dfs_main.cpp Nonrecursive_directed_dfs.cpp Nonrecursive_directed_dfs.h)
target_link_libraries(nonrecursive_directed_dfs_main std_io utility ${Boost_LIBRARIES})

add_executable(out_main out_main.cpp Out.cpp Out.h) # TODO:)
target_link_libraries(out_main std_io utility ${Boost_LIBRARIES})

add_executable(particle_main particle_main.cpp Particle.cpp Particle.h)
target_link_libraries(particle_main std_io utility ${Boost_LIBRARIES})

add_executable(patricia_set_main patricia_set_main.cpp Patricia_set.cpp Patricia_set.h)
target_link_libraries(patricia_set_main std_io utility ${Boost_LIBRARIES})

add_executable(patricia_st_main patricia_st_main.cpp Patricia_st.cpp Patricia_st.h)
target_link_libraries(patricia_st_main std_io utility ${Boost_LIBRARIES})

add_executable(picture_dump_main picture_dump_main.cpp)
target_link_libraries(picture_dump_main std_io utility ${Boost_LIBRARIES})

add_executable(picture_main picture_main.cpp Picture.cpp Picture.h) # TODO)
target_link_libraries(picture_main std_io utility ${Boost_LIBRARIES})

add_executable(point_2d_main point_2d_main.cpp Point_2d.cpp Point_2d.h)
target_link_libraries(point_2d_main std_io utility ${Boost_LIBRARIES})

add_executable(prim_mst_main prim_mst_main.cpp Prim_mst.cpp Prim_mst.h)
target_link_libraries(prim_mst_main std_io utility ${Boost_LIBRARIES})

add_executable(quick_find_uf_main quick_find_uf_main.cpp Quick_find_uf.cpp Quick_find_uf.h)
target_link_libraries(quick_find_uf_main std_io utility ${Boost_LIBRARIES})

add_executable(quick_union_uf_main quick_union_uf_main.cpp Quick_union_uf.cpp Quick_union_uf.h)
target_link_libraries(quick_union_uf_main std_io utility ${Boost_LIBRARIES})

add_executable(rabin_karp_main rabin_karp_main.cpp Rabin_karp.cpp Rabin_karp.h)
target_link_libraries(rabin_karp_main std_io utility ${Boost_LIBRARIES})

add_executable(random_seq_main random_seq_main.cpp)
target_link_libraries(random_seq_main std_io utility ${Boost_LIBRARIES})

add_executable(rect_hv_main rect_hv_main.cpp Rect_hv.cpp Rect_hv.h)
target_link_libraries(rect_hv_main std_io utility ${Boost_LIBRARIES})

add_executable(resizing_array_bag_main resizing_array_bag_main.cpp Resizing_array_bag.h)
target_link_libraries(resizing_array_bag_main std_io utility ${Boost_LIBRARIES})

add_executable(resizing_array_queue_main resizing_array_queue_main.cpp Resizing_array_queue.h)
target_link_libraries(resizing_array_queue_main std_io utility ${Boost_LIBRARIES})

add_executable(resizing_array_stack_main resizing_array_stack_main.cpp Resizing_array_stack.h)
target_link_libraries(resizing_array_stack_main std_io utility ${Boost_LIBRARIES})

add_executable(run_length_main run_length_main.cpp Run_length.cpp Run_length.h)
target_link_libraries(run_length_main std_io utility ${Boost_LIBRARIES})

add_executable(segment_tree_main segment_tree_main.cpp Segment_tree.cpp Segment_tree.h)
target_link_libraries(segment_tree_main std_io utility ${Boost_LIBRARIES})

add_executable(separate_chaining_hash_st_main separate_chaining_hash_st_main.cpp Separate_chaining_hash_st.cpp Separate_chaining_hash_st.h) # TODO)
target_link_libraries(separate_chaining_hash_st_main std_io utility ${Boost_LIBRARIES})

add_executable(sequential_search_st_main sequential_search_st_main.cpp Sequential_search_st.h)
target_link_libraries(sequential_search_st_main std_io utility ${Boost_LIBRARIES})

add_executable(sparse_vector_main sparse_vector_main.cpp Sparse_vector.cpp Sparse_vector.h)
target_link_libraries(sparse_vector_main std_io utility ${Boost_LIBRARIES})

add_executable(std_array_io_main std_array_io_main.cpp Std_array_io.cpp Std_array_io.h)
target_link_libraries(std_array_io_main std_io utility ${Boost_LIBRARIES})

add_executable(std_audio_main std_audio_main.cpp Std_audio.cpp Std_audio.h) # TODO)
target_link_libraries(std_audio_main utility ${Boost_LIBRARIES} ${QT_LIBRARIES})

add_executable(std_draw_main std_draw_main.cpp Std_draw.cpp Std_draw.h) # TODO)
target_link_libraries(std_draw_main std_io utility ${Boost_LIBRARIES})

add_executable(std_stats_main std_stats_main.cpp Std_stats.cpp Std_stats.h)
target_link_libraries(std_stats_main std_io utility ${Boost_LIBRARIES})

add_executable(stopwatch_cpu_main stopwatch_cpu_main.cpp Stopwatch_cpu.cpp Stopwatch_cpu.h)
target_link_libraries(stopwatch_cpu_main std_io utility ${Boost_LIBRARIES})

add_executable(stopwatch_main stopwatch_main.cpp Stopwatch.cpp Stopwatch.h)
target_link_libraries(stopwatch_main std_io utility ${Boost_LIBRARIES})

add_executable(suffix_array_main suffix_array_main.cpp Suffix_array.cpp Suffix_array.h)
target_link_libraries(suffix_array_main std_io utility ${Boost_LIBRARIES})

add_executable(suffix_array_x_main suffix_array_x_main.cpp Suffix_array_x.cpp Suffix_array_x.h)
target_link_libraries(suffix_array_x_main std_io utility ${Boost_LIBRARIES})

add_executable(symbol_digraph_main symbol_digraph_main.cpp Symbol_digraph.cpp Symbol_digraph.h)
target_link_libraries(symbol_digraph_main std_io utility ${Boost_LIBRARIES})

add_executable(symbol_graph_main symbol_graph_main.cpp Symbol_graph.cpp Symbol_graph.h)
target_link_libraries(symbol_graph_main std_io utility ${Boost_LIBRARIES})

add_executable(symbol_table_main symbol_table_main.cpp Symbol_table.cpp Symbol_table.h)
target_link_libraries(symbol_table_main std_io utility ${Boost_LIBRARIES})

add_executable(tarjan_scc_main tarjan_scc_main.cpp Tarjan_scc.cpp Tarjan_scc.h)
target_link_libraries(tarjan_scc_main std_io utility ${Boost_LIBRARIES})

add_executable(three_sum_fast_main three_sum_fast_main.cpp)
target_link_libraries(three_sum_fast_main std_io utility ${Boost_LIBRARIES})

add_executable(three_sum_main three_sum_main.cpp Three_sum.cpp Three_sum.h)
target_link_libraries(three_sum_main std_io utility ${Boost_LIBRARIES})

add_executable(top_m_main top_m_main.cpp Three_sum_fast.cpp Three_sum_fast.h)
target_link_libraries(top_m_main std_io utility ${Boost_LIBRARIES})

add_executable(topological_x_main topological_x_main.cpp Topological_x.cpp Topological_x.h)
target_link_libraries(topological_x_main std_io utility ${Boost_LIBRARIES})

add_executable(transaction_main transaction_main.cpp Transaction.cpp Transaction.h)
target_link_libraries(transaction_main std_io utility ${Boost_LIBRARIES})

add_executable(transitive_closure_main transitive_closure_main.cpp Transitive_closure.cpp Transitive_closure.h)
target_link_libraries(transitive_closure_main std_io utility ${Boost_LIBRARIES})

add_executable(trie_set_main trie_set_main.cpp Trie_set.cpp Trie_set.h)
target_link_libraries(trie_set_main std_io utility ${Boost_LIBRARIES})

add_executable(trie_st_main trie_st_main.cpp Trie_st.cpp Trie_st.h)
target_link_libraries(trie_st_main std_io utility ${Boost_LIBRARIES})

add_executable(tst_main tst_main.cpp TST.cpp TST.h)
target_link_libraries(tst_main std_io utility ${Boost_LIBRARIES})

add_executable(two_person_zero_sum_game_main two_person_zero_sum_game_main.cpp Two_person_zero_sum_game.cpp Two_person_zero_sum_game.h)
target_link_libraries(two_person_zero_sum_game_main std_io utility ${Boost_LIBRARIES})

add_executable(vector_main vector_main.cpp Vector.cpp Vector.h)
target_link_libraries(vector_main std_io utility ${Boost_LIBRARIES})
