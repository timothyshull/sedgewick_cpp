#ifndef MSD_RADIX_SORT_H
#define MSD_RADIX_SORT_H

#include <vector>
#include "utility.h"

namespace MSD_radix_sort {
    static const int bits_per_byte = 8;

    static const int bits_per_int = 32;

    static const int radix = 256;

    static const int cutoff = 15;

    void sort(std::vector<std::string>& a);

    int char_at(std::string& s, int d);

    void sort(std::vector<std::string>& a, int lo, int hi, int d, std::vector<std::string>& aux);

    void insertion(std::vector<std::string>& a, int lo, int hi, int d);

    void exch(std::vector<std::string>& a, int i, int j);

    bool less(std::string& v, std::string& w, int d);

    void sort(std::vector<int>& a);

    void sort(std::vector<int>& a, int lo, int hi, int d, std::vector<int>& aux);

    static void insertion(std::vector<int>& a, int lo, int hi, int d);

    static void exch(std::vector<int>& a, int i, int j);
};

#endif // MSD_RADIX_SORT_H
