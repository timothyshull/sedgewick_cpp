#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Bag.h"

using namespace testing;

TEST(Bag, add_5_check_size)
{
    Bag<int> bag;
    bag.add(1);
    bag.add(2);
    bag.add(3);
    bag.add(4);
    bag.add(5);
    
    ASSERT_THAT(bag.size(), Eq(5));
}

TEST(Bag, add_5_check_iterator)
{
    Bag<int> bag;
    bag.add(1);
    bag.add(2);
    bag.add(3);
    bag.add(4);
    bag.add(5);

    std::vector<int> v;
    auto it = bag.begin();
    v.push_back(*it);
    ++it;
    v.push_back(*it);
    ++it;
    v.push_back(*it);
    ++it;
    v.push_back(*it);
    ++it;
    v.push_back(*it);

    ASSERT_THAT(v, ContainerEq(std::vector<int> {5, 4, 3, 2, 1}));
    ASSERT_FALSE(it.has_next());
}

TEST(Bag, add_5_to_str)
{
    Bag<int> bag;
    bag.add(1);
    bag.add(2);
    bag.add(3);
    bag.add(4);
    bag.add(5);

    ASSERT_THAT(bag.to_string(), Eq("Bag(\n    5,\n    4,\n    3,\n    2,\n    1,\n)"));
}

