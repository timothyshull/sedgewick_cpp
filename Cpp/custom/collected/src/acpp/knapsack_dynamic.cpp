// Program 5.13 - Knapsack problem (dynamic programming)
#include "knapsack_dynamic.h"

int knapsack(int m)
{
    int i, space, max, maxi = 0, t;
    if (maxKnown[m] != unknown) { return maxKnown[m]; }
    for (i = 0, max = 0; i < N; i++) {
        if ((space = m - items[i].size) >= 0) {
            if ((t = knap(space) + items[i].val) > max) {
                max = t;
                maxi = i;
            }
        }
    }
    maxKnown[m] = max;
    itemKnown[m] = items[maxi];
    return max;
}