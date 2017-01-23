#ifndef TIMSORT_PY_H
#define TIMSORT_PY_H

#include <vector>

namespace Timsort_py {
    template <typename T>
    bool rich_compare();

    // assumes a -1, 0, 1
    template <typename T, typename Comparator>
    bool is_less_than(T& x, T& y) {
        static_assert(!std::is_same<Comparator, void>::value, "");
        return Comparator{}(x, y) < 0;
    }


    template <typename T>
    void sort(std::vector<T>& self) {

    }
};

#endif // TIMSORT_PY_H
