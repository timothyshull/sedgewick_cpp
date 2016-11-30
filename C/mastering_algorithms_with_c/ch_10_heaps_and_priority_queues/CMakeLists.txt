cmake_minimum_required(VERSION 3.6)
project(ch_10_heaps_and_priority_queues)

set(CMAKE_CXX_STANDARD 11)

add_executable(heap heap.c heap.h)
add_executable(parcels parcels.c parcels.h pqueue.h parcel.h)
add_executable(ex-1_2 ex-1_2.c)
add_executable(ex-1 ex-1.c)
