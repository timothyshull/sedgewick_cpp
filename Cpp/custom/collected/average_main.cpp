#include<iostream>

int main() {
    int count{0};
    double sum{0.0};

    std::string line;
    for (; std::getline(std::cin, line) && line != "";) {
        double value = atof(line.c_str());
        sum += value;
        count++;
    }

    double average = sum / count;

    std::cout << "The average is: " << average << "\n";

    return 0;
}
