// Program 4.17 - Complex numbers driver (roots of unity)
#include <iostream>
#include <cmath>
#include "Complex.h"

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    std::cout << size << " complex roots of unity" << "\n";
    double theta;
    for (auto k = 0; k < size; ++k) {
        theta = 2.0 * 3.14159 * k / size;
        Complex t{std::cos(theta), std::sin(theta)};
        Complex x{t};
        std::cout << k << ": " << t << "  ";
        for (auto j = 0; j < size - 1; ++j) { x *= t; }
        std::cout << x << "\n";
    }
    return 0;
}
