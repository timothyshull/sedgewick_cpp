#include <iostream>
#include "Bucket_sort.h"

int main()
{
    std::vector<float> test1{0.897, 0.565, 0.656, 0.1234, 0.665, 0.3434};
    bucket_sort(test1);

    for (auto f : test1) { std::cout << f << " "; }
    return 0;
}