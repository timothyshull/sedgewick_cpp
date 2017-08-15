#include <iostream>

#include "Std_in.h"
#include "Std_out.h"

int main()
{
    auto count = 0;
    auto sum = 0.0;

    auto dv = Std_in::read_all_doubles();
    for (auto d : dv) {
        sum += d;
        ++count;
    }

    auto average = sum / count;
    Std_out::print("The average is: {}\n", average);
    return 0;
}
