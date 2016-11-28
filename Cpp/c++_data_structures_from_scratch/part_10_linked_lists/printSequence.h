#ifndef PART_10_LINKED_LISTS_PRINTSEQUENCE_H
#define PART_10_LINKED_LISTS_PRINTSEQUENCE_H

#include <iostream>

namespace dss {
    template<class Iter>
    void printSequence(Iter begin, Iter end);

    template<class Iter>
    void printSequence(Iter begin, Iter end) {
        while (begin != end) {
            std::cout << *begin << ' ';
            ++begin;
        }
    }
};

#endif //PART_10_LINKED_LISTS_PRINTSEQUENCE_H
