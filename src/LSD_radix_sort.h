#ifndef LSD_RADIX_SORT_H
#define LSD_RADIX_SORT_H

#include <string>
#include <vector>
#include <limits>

#include "sort_utility.h"

// TODO: fix mismatch for template and bits value - s/b sizeof type
namespace LSD_radix_sort {
    using namespace Sort_utility;

    static const int bits_per_byte = std::numeric_limits<unsigned char>::digits;
    static const int bits = bits_per_byte * sizeof(int);
    static const int radix = 1 << bits_per_byte;
    static const int mask = radix - 1;
    static const int word = bits / bits_per_byte;

    void sort(std::vector<std::string> &a, int w);

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        auto n = coll.size();
        auto aux = std::vector<Item_t>(n);

        for (auto d = 0; d < word; ++d) {
            auto count = std::vector<int>(static_cast<typename std::vector<Item_t>::size_type>(radix + 1));
            for (auto i = 0; i < n; ++i) {
                auto c = (coll[i] >> bits_per_byte * d) & mask;
                count[c + 1] += 1;
            }

            for (auto r = 0; r < radix; ++r) {
                count[r + 1] += count[r];
            }

            if (d == word - 1) {
                auto shift1 = count[radix] - count[radix / 2];
                auto shift2 = count[radix / 2];
                for (auto r = 0; r < radix / 2; ++r) {
                    count[r] += shift1;
                }
                for (auto r = radix / 2; r < radix; ++r) {
                    count[r] -= shift2;
                }
            }

            for (auto i = 0; i < n; ++i) {
                auto c = (coll[i] >> bits_per_byte * d) & mask;
                aux[count[c]++] = coll[i];
            }

            for (auto i = 0; i < n; ++i) {
                coll[i] = aux[i];
            }
        }
    }
};

#endif // LSD_RADIX_SORT_H
