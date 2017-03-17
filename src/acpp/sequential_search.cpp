// Program 2.1 - Sequential search
#include "sequential_search.h"

int sequential_search(std::vector<int>& coll, int v, int l, int r)
{
    for (int i{l}; i <= r; ++i) {
        if (v == coll[i]) { return i; }
    }
    return -1;
}