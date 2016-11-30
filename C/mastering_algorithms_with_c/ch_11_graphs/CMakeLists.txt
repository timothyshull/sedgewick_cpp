cmake_minimum_required(VERSION 3.6)
project(ch_11_graphs)

set(CMAKE_CXX_STANDARD 11)

add_executable(graph graph.c graph.h set.c set.h)
add_executable(bfs bfs.c bfs.h list.c list.h queue.c queue.h)
add_executable(dfs dfs.c dfs.h list.c list.h queue.c queue.h)
