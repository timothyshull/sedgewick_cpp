#include<iostream>
#include<string>
#include<boost/lexical_cast.hpp>

#include"Accumulator.h"

int main(int argc, char *argv[]) {
    Accumulator<double> stats;
    std::string s;

    for (; std::getline(std::cin, s) && s != "";) {
        try {
            stats.add_value(boost::lexical_cast<double>(s));
        } catch (boost::bad_lexical_cast &e) {
            std::cerr << "Unable to cast " << s << "\n";
        }
    }

    std::cout << "Number of inputs: " << stats.count() << "\n";
    std::cout << "Mean: " << stats.mean() << "\n";
    std::cout << "Standard deviation: " << stats.std_dev() << "\n";
    std::cout << "Variance: " << stats.var() << "\n";

    return 0;
}
