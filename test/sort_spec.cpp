#include <list>
#include <random>

#include "Binary_insertion_sort.h"
#include "Bubblesort.h"
#include "Heap_sort.h"
#include "Insertion_sort.h"
#include "Insertion_sort_x.h"
// #include "LSD_radix_sort.h"
#include "Mergesort_bu.h"
#include "Mergesort.h"
#include "Mergesort_x.h"
// #include "MSD_radix_sort.h"
#include "Quicksort_3_string.h"
#include "Quicksort_3_way.h"
#include "Quicksort.h"
#include "Quicksort_x.h"
#include "Selection_sort.h"
#include "Shellsort.h"

#include "gtest/gtest.h"

#define SORT_TEST_FACTORY(Sort_namespace) TYPED_TEST(Sort_test, Sort_namespace)\
{\
    auto v = random_vector<TypeParam>();\
    Sort_namespace::sort(v);\
    EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));\
}

namespace {
    using namespace ::testing;

    template<typename Item_t>
    using Dist_t = typename std::conditional<
            std::is_floating_point<Item_t>::value,
            std::uniform_real_distribution<Item_t>,
            std::uniform_int_distribution<Item_t>
    >::type;

    template<typename Item_t>
    struct Sort_test : public ::testing::Test {};

    template<typename Item_t>
    std::vector<Item_t> random_vector(std::size_t num_elems = 1000)
    {
        std::random_device rd{};
        auto gen = std::default_random_engine{rd()};
        auto dist = Dist_t<Item_t>(0, 100);
        auto v = std::vector<Item_t>(num_elems);
        for (auto i = 0; i < num_elems; ++i) {
            v[i] = dist(gen);
        }
        return v;
    }

    // add back std::string later
    typedef ::testing::Types<char, int, unsigned int, long, float, double> Test_types;
    TYPED_TEST_CASE(Sort_test, Test_types);

    // TODO: turn into macro to reuse for different sort algorithms
//    TYPED_TEST(Sort_test, insertion_sort)
//    {
//        auto v = random_vector<TypeParam>();
//        Insertion_sort::sort(v);
//        EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
//    }

    SORT_TEST_FACTORY(Binary_insertion_sort)
    SORT_TEST_FACTORY(Bubblesort)
    SORT_TEST_FACTORY(Heap_sort)
    SORT_TEST_FACTORY(Insertion_sort)
    SORT_TEST_FACTORY(Insertion_sort_x)
//     SORT_TEST_FACTORY(LSD_radix_sort)
    SORT_TEST_FACTORY(Mergesort_bu)
    SORT_TEST_FACTORY(Mergesort)
//     SORT_TEST_FACTORY(Mergesort_x)
//     SORT_TEST_FACTORY(MSD_radix_sort)
//     SORT_TEST_FACTORY(Quicksort_3_string)
//     SORT_TEST_FACTORY(Quicksort_3_way)
    SORT_TEST_FACTORY(Quicksort)
    SORT_TEST_FACTORY(Quicksort_x)
    SORT_TEST_FACTORY(Selection_sort)
    SORT_TEST_FACTORY(Shellsort)
}