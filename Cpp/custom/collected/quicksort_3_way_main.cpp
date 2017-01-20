#include "Std_in.h"
#include "Quicksort_3_way.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Quicksort_3_way::sort(a);
    Quicksort_3_way::show(a);
    return 0;
}