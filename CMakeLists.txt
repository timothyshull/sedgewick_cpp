cmake_minimum_required(VERSION 3.8)
project(collected)

set(CMAKE_CXX_STANDARD 14)

set(GSL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gsl/include)

# for fmt printing lib
add_subdirectory(fmt)
include_directories(fmt/fmt)

add_subdirectory(src)
add_subdirectory(test)