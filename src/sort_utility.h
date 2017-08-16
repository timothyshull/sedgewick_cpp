#ifndef SORT_UTILITY_H
#define SORT_UTILITY_H

#include "Std_out.h"

namespace Sort_utility {
    template<typename Item_t>
    static void show(const std::vector<Item_t> &coll)
    {
        for (auto const &t : coll) {
            Std_out::print_line(t);
        }
    }
}

#endif //SORT_UTILITY_H
