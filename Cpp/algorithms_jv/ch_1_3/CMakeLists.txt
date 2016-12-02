cmake_minimum_required(VERSION 3.6)
project(ch_1_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(Linked_list Linked_list.h main.cpp utility.h Linked_bag.h Linked_queue.h Linked_stack.h)
add_executable(test_main catch.h test_main.cpp Linked_list.h Linked_list_spec.h Linked_list_spec.cpp)
add_executable(bag_stats bag_stats.cpp)
add_executable(djikstra_two_stack djikstra_two_stack.cpp Linked_stack.h utility.h)
add_executable(fcs_main fcs_main.cpp Fixed_capacity_stack.h)
add_executable(ras_main ras_main.cpp Resizing_array_stack.h)