#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Selection_sort.h"

using namespace testing;

TEST(Selection_sort, sort_no_comparator)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    Selection_sort::sort(v);
    ASSERT_THAT(v, Eq(std::vector<int>{1, 2, 3, 4, 5, 6}));
}

TEST(Selection_sort, sort_with_comparator)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    Selection_sort::sort<int, std::greater<int>>(v);
    ASSERT_THAT(v, Eq(std::vector<int>{6, 5, 4, 3, 2, 1}));
}

TEST(Selection_sort, is_sorted_true)
{
    auto v = std::vector<int>{1, 2, 3, 4, 5, 6};
    ASSERT_TRUE(Selection_sort::is_sorted<int>(v));
}

TEST(Selection_sort, is_sorted_false)
{
    auto v = std::vector<int>{2, 1, 3, 5, 6, 4};
    ASSERT_FALSE(Selection_sort::is_sorted<int>(v));
}

TEST(Selection_sort, show)
{
    auto v = std::vector<int>{1, 2, 3, 4, 5, 6};

    testing::internal::CaptureStdout();
    Selection_sort::show(v);
    auto output = std::string{testing::internal::GetCapturedStdout()};
    ASSERT_THAT(output, Eq(std::string{"1\n2\n3\n4\n5\n6\n"}));
}