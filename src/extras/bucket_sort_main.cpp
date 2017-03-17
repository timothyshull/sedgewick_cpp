#include <iostream>
#include <random>
#include "Bucket_sort.h"

int main()
{
    std::vector<float> test1{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    bucket_sort(test1);

    for (auto f : test1) { std::cout << f << "\n"; }

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{1, 100};

    std::vector<int> test2;
    for (int i{0}; i < 100; ++i) { test2.emplace_back(dis(gen)); }

    for (auto e : test2) { std::cout << e << "\n"; }
    bucket_sort(test2, 20);
    for (auto e : test2) { std::cout << e << "\n"; }
    return 0;
}