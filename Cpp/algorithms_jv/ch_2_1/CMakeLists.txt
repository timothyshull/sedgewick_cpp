cmake_minimum_required(VERSION 3.6)
project(ch_2_1)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.cpp Base_sort.h Selection_sort.h Insertion_sort.h Timer.h Sort_compare.h Shell_sort.h)
