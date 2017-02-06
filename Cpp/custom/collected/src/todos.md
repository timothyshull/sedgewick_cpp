- use only key/value pointers in symbol tables
- fix Tree structures to simplify node usage, remove all unnecessary using declarations from node based structures
- check if other trees are missing public delete and use remove for each
- red black bst has pointer access issues (nullptr being read in is_red)
- need to handle the empty string case for key comparators separately
- using a lambda with decltype as a comparator returns no matching constructor, need to handle both cases
- Std_in may still be passing empty strings in
- comparator still has issues, may not be setting key everywhere
- B_tree needs more work
- fix overload resolution issues in Insertion_sort
- review all "effective" guidelines and make code follow them
  e.g. make comparators (std::less) return false for ==
- convert all possible classes (with only static members etc) to namespaces (i.e. sorts)
- LSD_radix_sort has a bug that duplicates strings into the output vector
- fix Mergesort_x
- remove unnecessary comments
- review all uses of static and make sure they are necessary
- fix or make consistent all comparators, std::less, less, compareTo, etc
- fix imports between headers and .cpp when imports are in headers
- make sure all sort mains use a show and that all shows use range based for loop
- put all code in a global namespace
- any operations on the iterators in Min_pq and Max_pq may invalidate
  the size member, fix this
- use the ternary operator to check for nullptr where possible
```
std::string tmp(tmpPtrVal ? tmpPtrVal : "");
```
- use weak_ptr to return ptrs in structures
- be sure to fix usage of atoi -> per CERT security docs
- delete unnecessary iterators from node structures
- review locations where In and Out are used and replace replacements
- replace hashCode anywhere with std::hash overload
- move all tests/unitTest/checks to separate files and use catch or google test
- convert Std_in readAll to return one long string
- come back to Linked_bag, stack, queue etc
- make the I/O classes look more like std streams
- add iterators to all classes missing iterators
- move constants in Trie's to Trie class and make friend classes
- add overloads for ctors in In etc that take strings to take const char *
- add Stroustrup's args to vector utility function and process all argv with that
- double check all checks of argc
- add ostream << support to Point_2d
- add ostream support to Date
- Digraph generator Edge needs to be fixed
- check math_errorhandling and handle errno/MATH_ERRNO after cmath calls
- fix up str_to_num issues
- need Bipartite_x
- remove unnecessary container ctors where default ctor would be called
- fix null in Bellman_ford
- need to make a decision on where to use pointers and other options and
  be consistent (boost::optional)
- check Java Binary out/in etc for consistent IO format
- remove utility stream swap for swap member function
- need dtors in all node structures
- Binomial_min_pq iterator needs more work
- Boruvka_mst needs some fixes
- replace all old style for loops with iterators and range for loops where possible
- fix Stack, Queue, Etc and add const to all references that can be const
- Dijkstra_sp/undirected needs work
- fix iterator deal in Directed_eulerian_path and Directed_eulerian_cycle
- fix Doubling_ratio and Std_random::uniform(int, int) issues
- fix range for loops in Edge_weighted_graph
- fix up index_file
- fix up Adj_matrix_edge_weighted_digraph
- fix up Floyd_warshall
- declare in class definitions of operator== and operator!= friend
- rethink where Owning_node_pointers are deleted (if it truly owns it, the node should delete it)
- Index_min_binomial_queue needs dtor and node removal etc
- change all hash_code to return std::size_t
- review logical constness and usage
- assign const wherever possible
- !!!calling reserve on a vector and then assigning to an index does not work -> this is a big problem -> start with the resizing array classes
- review all comparators and remove Java compareTo format, default to < with == false
- review member ordering optimizations and reorder members accordingly
- review all substr calls
- review all string iterator usage and possibly switch with npos where applicable
- longest_common_substring and longest_repeated_substring main needs work
- review which classes can be turned into simple functions
- clean up Patricia_set, add node delete, add iterator support
- clean up Patricia_st and add ctor-> fix vale vs value pointer issue
- use smart pointers for all vectors etc holding pointers -> see segment_tree
- use size_t for all size functions
- fix key and value pointer issues in Sequential_search_st
- Symbol_digraph ctor needs more work
- more work in Symbol_table
- if all num_vertices, num_edges return size_t will not need to cast in ctors in so many places
- Make all priority_queues iterable
- Fix all trie class iterators
- more tests for In
- clean up all duplicated code between Input and Output type classes
- variance is wrong in accumulator
- all iterators may need duplicates with Const_iterator_type and const
- all classes with Std_in substituted for in need to be fixed
- all structures with pointer members need custom dtors, copy & assignment
    - AVL_tree_symbol_table
    - Bag
    - Binary_search_symbol_table
    - Binary_search_tree
    - Binomial_min_pq
    - Fibonacci_min_pq
    - Huffman
    - Index_binomial_min_pq
    - Index_fibonacci_min_pq
    - Linear_probing_hash_symbol_table
    - Patricia_mst
    - Queue
    - Red_black_bst
    - Separate_chaining_hash_st
    - Sequential_search_st
    - Stack
    - Std_draw
    - Trie_set
    - Trie_st
    - TST

- all classes with edges compared to nullptr need fixed
    - Collision_system
    - Dijkstra_sp
    - Dijkstra_undirected_sp

- replace all uses of Stack and Queue that were removed
- fix Queue and Bag iterators, ctors, dtor, etc
- fix and Double.NEGATIVE_INFINITY items that were replaced with positive_infinity
- add a const default edge to compare against
- fix all places where In class was replaced by ifstream, istream, stdin etc
- fix all edge pointer usage (Adj_matrix_edge_weighted_digraph)





# Notes
- for vector, use ctor reserve if type is not int type, otherwise use reserve





# Edge classes
Acyclic_lp
Acyclic_sp
Adj_matrix_edge_weighted_digraph
Assignment_problem
Bellman_ford_sp
Bipartite
Bipartite_x
Boruvka_mst
Breadth_first_directed_paths
Breadth_first_paths
Cycle
Depth_first_directed_paths
Depth_first_paths
Digraph
Digraph_generator
Dijkstra_all_pairs_sp
Dijkstra_sp
Dijkstra_undirected_sp
Directed_cycle
Directed_cycle_x
Directed_edge
directed_edge_main
Directed_eulerian_cycle
directed_eulerian_cycle_main
Directed_eulerian_path
directed_eulerian_path_main
Edge_weighted_digraph
Edge_weighted_directed_cycle
edge_weighted_directed_cycle_main
Edge_weighted_graph
edge_weighted_graph_main
Eulerian_cycle
eulerian_cycle_main
Eulerian_path
eulerian_path_main
Flow_edge
flow_edge_main
Flow_network
Floyd_warshall
floyd_warshall_main
Ford_fulkerson
ford_fulkerson_main
Graph
Graph_generator
graph_generator_main
Hopcroft_karp
hopcroft_karp_main
Kruskal_mst
kruskal_mst_main
Lazy_prim_mst
lazy_prim_mst_main
NFA
Prim_mst
prim_mst_main
Symbol_digraph
Symbol_graph
Topological_x
topological_x_main


# Node classes
AVL_tree_symbol_table
B_tree
Bag
Binary_search_tree
Binomial_min_pq
Fibonacci_min_pq
Huffman
Index_binomial_min_pq
Index_fibonacci_min_pq
Index_max_pq
Index_min_pq
Patricia_set
Patricia_st
Queue
Red_black_bst
Segment_tree
Sequential_search_st
Stack
Trie_set
Trie_st
TST