project(collected_test)

enable_testing()

add_subdirectory(googletest)

include_directories(../src)
include_directories(googletest/googletest/include)
include_directories(googletest/googlemock/include)

add_executable(accumulator_spec accumulator_spec.cpp)
target_link_libraries(accumulator_spec accumulator gtest gtest_main)

add_executable(bag_spec bag_spec.cpp ../src/Bag.h)
target_link_libraries(bag_spec std_io gtest gmock gtest_main)

add_executable(bubblesort_spec bubblesort_spec.cpp ../src/Bubblesort.h)
target_link_libraries(bubblesort_spec std_io gtest gmock gtest_main) # bubble lib

add_executable(selection_sort_spec selection_sort_spec.cpp ../src/Selection_sort.h)
target_link_libraries(selection_sort_spec std_io gtest gmock gtest_main) # selection lib

#add_executable(acyclic_lp_spec acyclic_lp_spec.cpp)
#target_link_libraries(acyclic_lp_spec googletest)


