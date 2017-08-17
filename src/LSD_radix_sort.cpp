#include "LSD_radix_sort.h"

void ::LSD_radix_sort::sort(std::vector<std::string> &coll, int w)
{
    auto n = coll.size();
    auto aux = std::vector<std::string>(n);

    for (auto d = w - 1; d >= 0; --d) {
        auto count = std::vector<int>(static_cast<std::vector<int>::size_type>(radix + 1));
        for (auto i = 0; i < n; ++i) {
            count[coll[i][d] + 1] += 1;
        }
        for (auto r = 0; r < radix; ++r) {
            count[r + 1] += count[r];
        }
        for (auto i = 0; i < n; ++i) {
            aux[count[coll[i][d]]++] = coll[i];
        }
        for (auto i = 0; i < n; ++i) {
            coll[i] = aux[i];
        }
    }
}
