#include <iostream>
#include <vector>

#include "Std_in.h"

int main()
{
    int count{0};
    double sum{0.0};

    std::vector<double> dv = Std_in::read_all_doubles();
    for (auto d : dv) {
        sum += d;
        ++count;
    }

    double average = sum / count;
    std::cout << "The average is: " << average << "\n";
    return 0;
}
