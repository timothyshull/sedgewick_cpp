#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Bubblesort.h"

using namespace testing;

TEST(Bubblesort, sort_no_comparator)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    Bubblesort::sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(Bubblesort, sort_with_comparator)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    Bubblesort::sort<int, std::greater<int>>(v);
    ASSERT_THAT(v, Eq(std::vector<int>{6, 5, 4, 3, 2, 1}));
}

TEST(Bubblesort, is_sorted_true)
{
    auto v = std::vector<int>{1, 2, 3, 4, 5, 6};
    ASSERT_TRUE(Bubblesort::is_sorted<int>(v));
}

TEST(Bubblesort, is_sorted_false)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    ASSERT_FALSE(Bubblesort::is_sorted<int>(v));
}

TEST(Bubblesort, show)
{
    auto v = std::vector<int>{1, 2, 3, 4, 5, 6};

    testing::internal::CaptureStdout();
    Bubblesort::show(v);
    auto output = std::string{testing::internal::GetCapturedStdout()};
    ASSERT_THAT(output, Eq(std::string{"1\n2\n3\n4\n5\n6\n"}));
}