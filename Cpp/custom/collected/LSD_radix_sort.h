#ifndef LSD_RADIX_SORT_H
#define LSD_RADIX_SORT_H

#include <string>
#include <vector>

namespace LSD_radix_sort {
    static const int bits_per_byte = 8;
    static const int bits = 32;
    static const int radix = 1 << bits_per_byte;
    static const int mask = radix - 1;
    static const int word = bits / bits_per_byte;

    static void sort(std::vector<std::string>& a, int w)
    {
        int n = a.size();
        std::vector<std::string> aux{};
        aux.reserve(static_cast<std::vector<std::string>::size_type>(n));

        for (int d = w - 1; d >= 0; --d) {
            std::vector<int> count{};
            count.reserve(static_cast<std::vector<int>::size_type>(radix + 1));
            for (int i = 0; i < n; ++i) {
                count[a[i][d] + 1] += 1;
            }

            for (int r = 0; r < radix; ++r) {
                count[r + 1] += count[r];
            }

            for (int i = 0; i < n; ++i) {
                aux[count[a[i][d]]++] = a[i];
            }

            for (int i = 0; i < n; ++i) {
                a[i] = aux[i];
            }
        }
    }

    static void sort(std::vector<int>& a)
    {
        int n = a.size();
        std::vector<int> aux{};
        aux.reserve(static_cast<std::vector<int>::size_type>(n));

        for (int d = 0; d < word; ++d) {
            std::vector<int> count{};
            count.reserve(static_cast<std::vector<int>::size_type>(radix + 1));
            for (int i = 0; i < n; ++i) {
                int c = (a[i] >> bits_per_byte * d) & mask;
                count[c + 1] += 1;
            }

            for (int r = 0; r < radix; ++r) {
                count[r + 1] += count[r];
            }

            if (d == word - 1) {
                int shift1 = count[radix] - count[radix / 2];
                int shift2 = count[radix / 2];
                for (int r = 0; r < radix / 2; ++r) {
                    count[r] += shift1;
                }
                for (int r = radix / 2; r < radix; ++r) {
                    count[r] -= shift2;
                }
            }

            for (int i = 0; i < n; ++i) {
                int c = (a[i] >> bits_per_byte * d) & mask;
                aux[count[c]++] = a[i];
            }

            for (int i = 0; i < n; ++i) {
                a[i] = aux[i];
            }
        }
    }
};

#endif // LSD_RADIX_SORT_H
