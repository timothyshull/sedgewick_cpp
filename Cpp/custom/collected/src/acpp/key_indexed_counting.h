// Program 6.17 - Key-indexed counting
#ifndef KEY_INDEXED_COUNTING_H
#define KEY_INDEXED_COUNTING_H

#include <vector>

void distribution_count(std::vector<int>& coll, int l, int r, std::size_t size)
{
    const static std::size_t max_size{1000};
    std::vector<int> count;
    count.assign(size, 0);
    static std::vector<int> aux;
    aux.reserve(max_size);

    int i;
    int j;
    for (i = l; i <= r; ++i) { count[coll[i] + 1]++; }
    for (j = 1; j < size; ++j) { count[j] += count[j - 1]; }
    for (i = l; i <= r; ++i) { aux[count[coll[i]]++] = coll[i]; }
    for (i = l; i <= r; ++i) { coll[i] = aux[i - l]; }
}

#endif // KEY_INDEXED_COUNTING_H
