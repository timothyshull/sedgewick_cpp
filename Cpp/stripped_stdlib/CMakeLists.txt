cmake_minimum_required(VERSION 3.6)
project(stripped_stdlib)

set(CMAKE_CXX_STANDARD 11)

add_executable(list.h list_main.cpp list.h)
add_executable(tree tree_main.cpp tree.h)
add_executable(hash_table hash_table_main.cpp hash_table.h)