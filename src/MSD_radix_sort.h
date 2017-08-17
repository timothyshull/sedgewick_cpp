#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include <vector>
#include <gsl/gsl_util>

#include "Insertion_sort.h"
#include "sort_utility.h"
#include "utility.h"


// TODO: fix mismatch in bits_per_int - s/b sizeof(type) with templates
namespace MSD_radix_sort {
    using namespace Sort_utility;

    static int const bits_per_byte = std::numeric_limits<unsigned char>::digits;
    static int const bits_per_int = sizeof(int) * bits_per_byte;
    static int const radix = 256;
    static int const cutoff = 15;

    void sort(std::vector<std::string> &coll);

    int char_at(std::string &s, int d);

    template<typename Item_t>
    void sort(std::vector<Item_t> &a, int lo, int hi, int d, std::vector<int> &aux)
    {
        if (hi <= lo + cutoff) {
            Insertion_sort::sort(a, lo, hi, d);
            return;
        }

        auto count = std::vector<int>(static_cast<std::vector<int>::size_type>(radix + 1));
        auto mask = radix - 1;
        auto shift = bits_per_int - bits_per_byte * d - bits_per_byte;
        for (auto i = lo; i <= hi; ++i) {
            auto c = (a[i] >> shift) & mask;
            count[c + 1]++;
        }

        for (auto r = 0; r < radix; ++r) {
            count[r + 1] += count[r];
        }

        // Sedgewick labeled as buggy -> review
        for (auto i = lo; i <= hi; ++i) {
            auto c = (a[i] >> shift) & mask;
            aux[count[c]++] = a[i];
        }

        for (auto i = lo; i <= hi; ++i) {
            a[i] = aux[i - lo];
        }

        if (d == 4) {
            return;
        }

        if (count[0] > 0) { sort(a, lo, lo + count[0] - 1, d + 1, aux); }
        for (auto r = 0; r < radix; ++r) {
            if (count[r + 1] > count[r]) {
                sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux);
            }
        }
    }

    template<typename Item_t>
    void sort(std::vector<Item_t> &coll)
    {
        auto n = gsl::narrow_cast<Item_t>(coll.size());
        auto aux = std::vector<Item_t>(static_cast<std::vector<Item_t>::size_type>(n));
        sort(coll, 0, n - 1, 0, aux);
    }

};

#endif // MSD_RADIX_SORT_H
