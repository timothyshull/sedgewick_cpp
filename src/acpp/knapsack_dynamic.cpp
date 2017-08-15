// Program 5.13 - Knapsack problem (dynamic programming)
#include <vector>
#include <string>
#include <random>
#include <deque>
#include <iostream>
#include <iomanip>
#include "knapsack_dynamic.h"

struct Item {
    int size;
    int val;
};

std::vector<int> max_known;

std::vector<Item> items;

std::vector<Item> item_known;

int unknown = -1;

int n = 1000;

int knapsack(int m)
{
    int i;
    int space;
    int max;
    auto max_i = 0;
    int t;
    if (max_known[m] != unknown) { return max_known[m]; }
    for (i = 0, max = 0; i < n; ++i) {
        if ((space = m - items[i].size) >= 0) {
            if ((t = knapsack(space) + items[i].val) > max) {
                max = t;
                max_i = i;
            }
        }
    }
    max_known[m] = max;
    item_known[m] = items[max_i];
    return max;
}

// http://introcs.cs.princeton.edu/java/23recursion/Knapsack.java.html
int main(int argc, char* argv[])
{
    //auto n1 = std::stoul(argv[0]);
    //auto max_weight = std::stoul(argv[1]);
    std::size_t n1 = 10;
    std::size_t max_weight = 20;

    std::vector<int> profit(n1 + 1);
    std::vector<int> weight(n1 + 1);

    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis1(1, 1000);
    std::uniform_int_distribution<> dis2(1, static_cast<int>(max_weight)); // narrow_cast
    for (auto n = 1; n <= n1; ++n) {
        profit[n] = dis1(gen);
        weight[n] = dis2(gen);
    }

    // opt[n][w] = max profit of packing items 1..n with weight limit w
    // sol[n][w] = does opt solution to pack items 1..n with weight limit w include item n?
    std::vector<std::vector<int>> options(n1 + 1, std::vector<int>(max_weight + 1));
    std::vector<std::deque<bool>> sol(n1 + 1, std::deque<bool>(max_weight + 1));

    int option1;
    int option2;
    for (auto n = 1; n <= n1; ++n) {
        for (auto w = 1; w <= max_weight; ++w) {
            option1 = options[n - 1][w];

            option2 = std::numeric_limits<int>::min();
            if (weight[n] <= w) { option2 = profit[n] + options[n - 1][w - weight[n]]; }

            options[n][w] = std::max(option1, option2);
            sol[n][w] = (option2 > option1);
        }
    }

    // determine which items to take
    std::deque<bool> take(n1 + 1);
    for (auto n = n1, w = max_weight; n > 0; --n) {
        if (sol[n][w]) {
            take[n] = true;
            w = w - weight[n];
        } else {
            take[n] = false;
        }
    }

    // print results
    std::cout << "item"
              << std::setw(8) << "profit"
              << std::setw(8) << "weight"
              << std::setw(8) << "take\n";
    for (auto n = 1; n <= n1; ++n) {
        std::cout << std::setw(2) << n
                  << std::setw(8) << profit[n]
                  << std::setw(8) << weight[n]
                  << std::setw(8) << take[n] << "\n";
    }
}







