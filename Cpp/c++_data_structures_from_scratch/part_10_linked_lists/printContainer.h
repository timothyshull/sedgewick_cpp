#ifndef PART_10_LINKED_LISTS_PRINTCONTAINER_H
#define PART_10_LINKED_LISTS_PRINTCONTAINER_H

#include <iostream>

#include "printSequence.h"

namespace dss {
    template<class Container>
    void printContainer(const Container &container);

    template<class Container>
    void printContainerReverse(const Container &container);

    template<class Container>
    inline void printContainer(const Container &container) {
        printSequence(container.begin(), container.end());
        std::cout << std::endl;
    }

    template<class Container>
    inline void printContainerReverse(const Container &container) {
        printSequence(container.rbegin(), container.rend());
        std::cout << std::endl;
    }
};

#endif //PART_10_LINKED_LISTS_PRINTCONTAINER_H
