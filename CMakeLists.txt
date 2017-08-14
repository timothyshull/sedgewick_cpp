cmake_minimum_required(VERSION 3.8)
project(collected)

set(CMAKE_CXX_STANDARD 14)

set(GSL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/GSL/include)

add_subdirectory(src)
add_subdirectory(test)