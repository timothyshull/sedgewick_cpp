cmake_minimum_required(VERSION 3.6)
project(ch_9_trees)

set(CMAKE_CXX_STANDARD 11)

add_executable(bitree bitree.c bitree.h)
add_executable(traverse traverse.c traverse.h list.c list.h)
add_executable(bistree bistree.c bistree.h)
add_executable(ex-1 ex-1.c)
add_executable(ex-1_2 ex-1_2.c)