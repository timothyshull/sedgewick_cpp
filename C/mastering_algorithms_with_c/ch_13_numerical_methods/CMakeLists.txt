cmake_minimum_required(VERSION 3.6)
project(ch_13_numerical_methods)

set(CMAKE_CXX_STANDARD 11)

add_executable(interpol interpol.c nummeths.h)
add_executable(lsqe lsqe.c nummeths.h)
add_executable(root root.c nummeths.h)
add_executable(ex-1 nummeths/ex-1.c nummeths.h)