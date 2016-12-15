cmake_minimum_required(VERSION 3.6)
project(collected)

set(CMAKE_CXX_STANDARD 11)

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(accumulator_main accumulator_main.cpp Accumulator.h)
add_executable(acyclic_lp_main acyclic_lp_main.cpp Acyclic_LP.h Edge_weighted_digraph.h Edge_weighted_digraph.cpp)
add_executable(edge_weighted_digraph_main.cpp Edge_weighted_digraph.cpp Edge_weighted_digraph.h)

add_executable(std_in_main std_in_main.cpp Std_in.h Std_in.cpp Scanner.h Scanner.cpp LRU_cache.h)

add_executable(set_main set_main.cpp Set.h)