#include "LSD_radix_sort.h"

void ::LSD_radix_sort::sort(std::vector<std::string>& a, int w)
{
    auto n = a.size();
    std::vector<std::string> aux(n);

    for (int d{w - 1}; d >= 0; --d) {
        std::vector<int> count(static_cast<std::vector<int>::size_type>(radix + 1));
        for (int i{0}; i < n; ++i) { count[a[i][d] + 1] += 1; }
        for (int r{0}; r < radix; ++r) { count[r + 1] += count[r]; }
        for (int i{0}; i < n; ++i) { aux[count[a[i][d]]++] = a[i]; }
        for (int i{0}; i < n; ++i) { a[i] = aux[i]; }
    }
}
