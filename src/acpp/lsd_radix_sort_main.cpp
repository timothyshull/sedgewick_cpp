#include <vector>
#include <random>
#include <iostream>
#include "lsd_radix_sort.h"

int main() {
    std::vector<int> test1;

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, 10000};

    for (int i{0}; i < 1000000; ++i) { test1.emplace_back(dis(gen)); }

    radix_sort(test1, 10, 5);
    for (auto e : test1) { std::cout << e << "\n"; }
    return 0;
}