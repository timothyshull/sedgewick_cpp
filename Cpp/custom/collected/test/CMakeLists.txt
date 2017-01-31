project(collected_test)

enable_testing()

add_subdirectory(googletest)

include_directories(../src)
include_directories(googletest/googletest/include)

add_executable(accumulator_spec accumulator_spec.cpp)
target_link_libraries(accumulator_spec accumulator gtest gtest_main)

add_executable(acyclic_lp_spec acyclic_lp_spec.cpp)
target_link_libraries(acyclic_lp_spec googletest)
