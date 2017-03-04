#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Accumulator.h"

using namespace testing;

TEST(Accumulator, default_ctor_count)
{
    Accumulator<double> stats;
    ASSERT_THAT(stats.count(), Eq(0));
    ASSERT_THAT(stats.mean(), Eq(0.0));
    ASSERT_THAT(stats.std_dev(), Eq(0.0));
    ASSERT_THAT(stats.var(), Eq(0.0));
}

TEST(Accumulator, count) {
    Accumulator<double> stats;
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    stats.add_data_value(1.0);
    std::clog << "Should have added 5 values\n";
    ASSERT_THAT(stats.count(), Eq(5));
}