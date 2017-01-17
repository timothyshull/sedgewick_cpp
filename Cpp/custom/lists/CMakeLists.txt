cmake_minimum_required(VERSION 3.6)
project(lists)

set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/Cellar/GSL/master/include)

#add_executable(main main.cpp simplified_std_list.h smart_list.h)
#add_executable(main main.cpp smart_list.h)
add_executable(main main.cpp Doubly_linked_list.h)
