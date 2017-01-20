#include <vector>
#include "utility.h"
#include "Std_in.h"
#include "Quicksort_x.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Quicksort_x::sort(a);
    utility::assert(Quicksort_x::is_sorted(a), "The Quicksort_x is_sorted check failed");
    Quicksort_x::show(a);
    return 0;
}