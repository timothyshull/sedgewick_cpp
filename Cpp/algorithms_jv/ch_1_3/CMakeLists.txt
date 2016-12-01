cmake_minimum_required(VERSION 3.6)
project(ch_1_3)

set(CMAKE_CXX_STANDARD 11)

add_executable(Linked_list Linked_list.h main.cpp utility.h Linked_bag.h Linked_queue.h Linked_stack.h)
add_executable(test_main catch.h test_main.cpp Linked_list.h Linked_list_spec.h Linked_list_spec.cpp)