// Program 6.5 - Shellsort
#ifndef SHELLSORT_H
#define SHELLSORT_H

#include <vector>

template<typename Item_type>
void shellsort(std::vector<Item_type> coll, int l, int r)
{
    int h;
    for (h = 1; h <= (r - l) / 9; h = 3 * h + 1) {}

    for (; h > 0; h /= 3) {
        for (int i{l + h}; i <= r; ++i) {
            int j{i};

            Item_type v = coll[i];
            while (j >= l + h && v < coll[j - h]) {
                coll[j] = coll[j - h];
                j -= h;
            }

            coll[j] = v;
        }
    }
}

#endif // SHELLSORT_H
