#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Accumulator.h"

using namespace testing;

TEST(Accumulator, default_ctor_count)
{
    auto stats = Accumulator{};
    ASSERT_THAT(stats.count(), Eq(0));
    ASSERT_THAT(stats.mean(), Eq(0.0));
    ASSERT_THAT(stats.std_dev(), Eq(0.0));
    ASSERT_THAT(stats.var(), Eq(0.0));
}

TEST(Accumulator, count) {
    auto stats = Accumulator{};
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    ASSERT_THAT(stats.count(), Eq(5));
}