#ifndef KNUTH_SHUFFLE_H
#define KNUTH_SHUFFLE_H

#include <random>
#include "Std_random.h"

namespace Knuth {
    template<typename T>
    void shuffle(std::vector<T>& a)
    {
        int n = a.size();
        for (int i = 0; i < n; i++) {
            int r = i + static_cast<int>(Std_random::uniform() * (n - i));
            T swap = a[r];
            a[r] = a[i];
            a[i] = swap;
        }
    }
}

#endif //KNUTH_SHUFFLE_H
