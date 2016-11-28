cmake_minimum_required(VERSION 3.6)
project(part_10_linked_lists)

set(CMAKE_CXX_STANDARD 11)

add_executable(list main.cpp ListNode.h ListIter.h List.h Allocator.h ConstIter.h ReverseIter.h printContainer.h printSequence.h)
