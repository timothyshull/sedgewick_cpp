#ifndef LSD_RADIX_SORT_H
#define LSD_RADIX_SORT_H

#include <string>
#include <vector>

// TODO: fix mismatch for template and bits value - s/b sizeof type
namespace LSD_radix_sort {
    static const int bits_per_byte = CHAR_BIT;

    static const int bits = bits_per_byte * sizeof(int);

    static const int radix = 1 << bits_per_byte;

    static const int mask = radix - 1;

    static const int word = bits / bits_per_byte;

    void sort(std::vector<std::string>& a, int w);

    template<typename Item_type>
    void sort(std::vector<Item_type>& a)
    {
        auto n = a.size();
        std::vector<Item_type> aux(n);

        for (int d{0}; d < word; ++d) {
            std::vector<int> count(static_cast<typename std::vector<Item_type>::size_type>(radix + 1));
            for (int i{0}; i < n; ++i) {
                int c = (a[i] >> bits_per_byte * d) & mask;
                count[c + 1] += 1;
            }

            for (int r{0}; r < radix; ++r) { count[r + 1] += count[r]; }

            if (d == word - 1) {
                int shift1 = count[radix] - count[radix / 2];
                int shift2 = count[radix / 2];
                for (int r{0}; r < radix / 2; ++r) { count[r] += shift1; }
                for (int r{radix / 2}; r < radix; ++r) { count[r] -= shift2; }
            }

            for (int i{0}; i < n; ++i) {
                int c = (a[i] >> bits_per_byte * d) & mask;
                aux[count[c]++] = a[i];
            }

            for (int i{0}; i < n; ++i) { a[i] = aux[i]; }
        }
    }
};

#endif // LSD_RADIX_SORT_H
