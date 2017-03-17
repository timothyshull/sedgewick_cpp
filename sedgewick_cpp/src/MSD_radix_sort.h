#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include <vector>
#include "utility.h"

// TODO: fix mismatch in bits_per_int - s/b sizeof(type) with templates
namespace MSD_radix_sort {
    static const int bits_per_byte = CHAR_BIT;

    static const int bits_per_int = sizeof(int) * CHAR_BIT;

    static const int radix = 256;

    static const int cutoff = 15;

    void sort(std::vector<std::string>& a);

    int char_at(std::string& s, int d);

    void sort(std::vector<std::string>& a, int lo, int hi, int d, std::vector<std::string>& aux);

    void insertion(std::vector<std::string>& a, int lo, int hi, int d);

    void exch(std::vector<std::string>& a, int i, int j);

    bool less(std::string& v, std::string& w, int d);

    template<typename Item_type>
    void sort(std::vector<Item_type>& a)
    {
        std::vector<Item_type> aux(a.size());
        sort(a, 0, static_cast<Item_type>(a.size() - 1), 0, aux); // narrow_cast
    }

    template<typename Item_type>
    void sort(std::vector<Item_type>& a, int lo, int hi, int d, std::vector<int>& aux)
    {
        if (hi <= lo + cutoff) {
            insertion(a, lo, hi, d);
            return;
        }

        std::vector<int> count(static_cast<std::vector<int>::size_type>(radix + 1));
        int mask{radix - 1};
        int shift{bits_per_int - bits_per_byte * d - bits_per_byte};
        for (int i{lo}; i <= hi; ++i) {
            int c{(a[i] >> shift) & mask};
            count[c + 1]++;
        }

        for (int r{0}; r < radix; ++r) { count[r + 1] += count[r]; }

        // Sedgewick labeled as buggy -> review
        for (int i{lo}; i <= hi; ++i) {
            int c{(a[i] >> shift) & mask};
            aux[count[c]++] = a[i];
        }

        for (int i{lo}; i <= hi; ++i) { a[i] = aux[i - lo]; }

        if (d == 4) { return; }

        if (count[0] > 0) { sort(a, lo, lo + count[0] - 1, d + 1, aux); }
        for (int r{0}; r < radix; ++r) {
            if (count[r + 1] > count[r]) { sort(a, lo + count[r], lo + count[r + 1] - 1, d + 1, aux); }
        }
    }

    template<typename Item_type>
    void insertion(std::vector<Item_type>& a, int lo, int hi, int d)
    {
        for (int i{lo}; i <= hi; ++i) {
            for (int j{i}; j > lo && a[j] < a[j - 1]; j--) {
                exch(a, j, j - 1);
            }
        }
    }

    template<typename Item_type>
    void exch(std::vector<Item_type>& a, int i, int j)
    {
        Item_type temp = a[i];
        a[i] = a[j];
        a[j] = temp;
    }
};

#endif // MSD_RADIX_SORT_H
