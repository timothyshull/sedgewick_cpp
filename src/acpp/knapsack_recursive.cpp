// Program 5.12 - Knapsack problem (recursive implementation)
#include "knapsack_recursive.h"

int knapsack(int cap)
{
    int i;
    int space;
    int max;
    int t;
    for (i = 0, max = 0; i < N; ++i) {
        if ((space = cap - items[i].size) >= 0) {
            if ((t = knapsack(space) + items[i].val) > max) {
                max = t;
            }
        }
    }
    return max;
}