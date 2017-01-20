#include <string>
#include <vector>
#include "Std_in.h"
#include "Insertion_sort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Insertion_sort::sort<std::string>(a);
    Insertion_sort::show(a);
    return 0;
}