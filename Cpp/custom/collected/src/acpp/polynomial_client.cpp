#include <iostream>
#include "Polynomial.h"

int main(int argc, char* argv[])
{
    int size{std::stoi(argv[1])};
    double p{std::stod(argv[2])};
    std::cout << "Binomial coefficients" << "\n";
    Polynomial<int> x{1, 1};
    Polynomial<int> one{1, 0};
    Polynomial<int> t{x + one};
    Polynomial<int> y{t};
    for (int i{0}; i < size; ++i) {
        y = y * t;
        std::cout << y << "\n";
    }
    std::cout << y.eval(p) << "\n";
    return 0;
}