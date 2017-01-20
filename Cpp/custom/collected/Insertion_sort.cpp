#include <vector>
#include "Insertion_sort.h"

void ::Insertion_sort::exch(std::vector<int> a, int i, int j)
{
    int swap = a[i];
    a[i] = a[j];
    a[j] = swap;
}
