#ifndef SELECTION_SORT_H
#define SELECTION_SORT_H

#include <algorithm>

#include "utility.h"
#include "Std_out.h"

namespace Selection_sort {
    // removed
    // bool less(T& v, T& w);
    // bool less(T& v, T& w);
    // void exch(std::vector<T>& a, int i, int j);
    // void sort(std::vector<T>& a) with just a T template arg

    // forward declarations
    template<typename Item_t, typename Comparator_type = std::less<Item_t>>
    void sort(std::vector<Item_t>& a);

//    template<typename Item_t>
//    bool is_sorted(std::vector<Item_t>& a);
//
//    template<typename Item_t>
//    bool is_sorted(std::vector<Item_t>& a, int lo, int hi);

    template<typename Item_t, typename Comparator_type = std::less<Item_t>>
    bool is_sorted(std::vector<Item_t>& a);

    template<typename Item_t, typename Comparator_type = std::less<Item_t>>
    bool is_sorted(std::vector<Item_t>& a, int lo, int hi);

    // begin definitions
    template<typename Item_t, typename Comparator_type>
    void sort(std::vector<Item_t>& a)
    {
        Comparator_type comp;

        auto n = a.size();
        for (auto i = 0; i < n; ++i) {
            int min = i;
            for (auto j = i + 1; j < n; ++j) {
                if (comp(a[j], a[min])) { min = j; }
            }
            std::swap(a[i], a[min]);
#ifdef ACPP_DEBUG
            utility::alg_assert(is_sorted<Item_t, Comparator_type>(a, 0, i), "Selection_sort is_sorted range _check failed");
#endif
        }
#ifdef ACPP_DEBUG
        utility::alg_assert(is_sorted<Item_t, Comparator_type>(a), "Selection_sort is_sorted _check failed");
#endif
    }

//    template<typename Item_t>
//    inline bool is_sorted(std::vector<Item_t>& a) { return is_sorted(a, 0, a.size() - 1); }
//
//    template<typename Item_t>
//    bool is_sorted(std::vector<Item_t>& a, int lo, int hi)
//    {
//        for (auto i = lo + 1; i <= hi; ++i) {
//            if (std::less<Item_t>{}(a[i], a[i - 1])) { return false; }
//        }
//        return true;
//    }

    template<typename Item_t, typename Comparator_type>
    bool is_sorted(std::vector<Item_t>& a) { return is_sorted<Item_t, Comparator_type>(a, 0, static_cast<int>(a.size() - 1)); } // narrow_cast

    template<typename Item_t, typename Comparator_type>
    bool is_sorted(std::vector<Item_t>& a, int lo, int hi)
    {
        Comparator_type comp;
        for (auto i = lo + 1; i <= hi; ++i) {
            if (comp(a[i], a[i - 1])) {
                return false;
            }
        }
        return true;
    }

    template<typename Item_t>
    inline void show(std::vector<Item_t>& a) { for (auto t : a) { Std_out::print_line(t); }}
};

#endif // SELECTION_SORT_H
