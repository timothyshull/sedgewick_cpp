#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

#include <type_traits>
#include <vector>

namespace Binary_search {
    template<typename Integral_type>
    Integral_type index_of(std::vector<Integral_type>& a, Integral_type& key)
    {
        static_assert(std::is_integral<Integral_type>::value, "Integral type required");
        Integral_type lo = 0;
        Integral_type hi = a.size();
        while (lo <= hi) {
            Integral_type mid = lo + (hi - lo) / 2;
            if (key < a[mid]) {
                hi = mid - 1;
            } else if (key > a[mid]) {
                lo = mid + 1;
            } else {
                return mid;
            }
        }
        return -1;
    };

    template<typename Integral_type>
    Integral_type rank(Integral_type& key, std::vector<Integral_type>& a)
    {
        return index_of(a, key);
    }
}

#endif // BINARY_SEARCH_H
