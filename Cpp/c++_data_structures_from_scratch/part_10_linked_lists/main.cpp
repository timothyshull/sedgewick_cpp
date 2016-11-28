#include <iostream>

#include "List.h"
#include "printContainer.h"

int main() {
    using namespace std;
    using namespace dss;

    List<int> s;

    for (int i = 0; i != 10; ++i)
        s.push_back(i);

    printContainerReverse(s);

    return 0;
}