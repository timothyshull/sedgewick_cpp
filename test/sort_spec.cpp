#include <list>
#include <random>

#include "Insertion_sort.h"
#include "Selection_sort.h"

#include "gtest/gtest.h"

namespace {
    using namespace ::testing;

    template<bool b, typename True_t, typename False_t>
    using Conditional = typename std::conditional<b, True_t, False_t>::type;

    template<typename Item_t>
    using Dist_t = Conditional<
            std::is_floating_point<Item_t>::value,
            std::uniform_real_distribution<Item_t>,
            std::uniform_int_distribution<Item_t>
    >;

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
    TYPED_TEST(Sort_test, insertion_sort)
    {
        auto v = random_vector<TypeParam>();
        Insertion_sort::sort(v);
        EXPECT_TRUE(std::is_sorted(v.begin(), v.end()));
    }
}