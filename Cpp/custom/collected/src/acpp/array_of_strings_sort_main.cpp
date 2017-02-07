// Program 3.17 - Sorting an array of strings
#include <iostream>
#include <vector>

#include "array_of_strings_sort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a;
    a.reserve(a.max_size());

    int i;
    std::string line;
    for (i = 0; i < a.max_size(); ++i) {
        std::getline(std::cin, line);
        if (!line.empty()) {
            a[i] = line;
        } else {
            break;
        }
    }
    a.shrink_to_fit();
    sort(a);
    for (auto s : a) {
        std::cout << s << "\n";
    }
    return 0;
}