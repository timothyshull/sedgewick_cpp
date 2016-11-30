cmake_minimum_required(VERSION 3.6)
project(ch_8_hash_tables)

set(CMAKE_CXX_STANDARD 11)

add_executable(chtbl chtbl.c chtbl.h list.c list.h)
add_executable(ex-1_2 ex-1_2.c)
add_executable(ex-1 ex-1.c)
add_executable(hashpjw hashpjw.c hashpjw.h)
add_executable(ohtbl ohtbl.c ohtbl.h)
add_executable(lex lex.c lex.h symbol.h)
