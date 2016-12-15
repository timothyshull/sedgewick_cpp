#include<iostream>

#include"Std_in.h"

int main() {
    Std_in std_in{};
    std::cout << Std_in::locale.name().c_str() << "\n";
    return 0;
}