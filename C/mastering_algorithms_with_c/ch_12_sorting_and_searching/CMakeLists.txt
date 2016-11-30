cmake_minimum_required(VERSION 3.6)
project(ch_12_sorting_and_searching)

set(CMAKE_CXX_STANDARD 11)

add_executable(bisearch bisearch.c sort.h)
add_executable(ctsort ctsort.c sort.h)
add_executable(directls directls.c sort.h)
add_executable(issort issort.c sort.h)
add_executable(mgsort mgsort.c sort.h)
add_executable(qksort qksort.c sort.h)
add_executable(rxsort rxsort.c sort.h)
add_executable(spell spell.c spell.h sort.h search.h)