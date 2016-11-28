cmake_minimum_required(VERSION 3.6)
project(ch_5_linked_lists)

set(CMAKE_CXX_STANDARD 11)

add_executable(main main.c dlist.h dlist.c list.h list.c clist.h clist.c)

add_executable(frames frames.h frames.c list.h list.c)

add_executable(page page.h page.c clist.h clist.c)
