#include <string>
#include <vector>
#include "Std_in.h"
#include "Shellsort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Shellsort::sort(a);
    Shellsort::show(a);
    return 0;
}