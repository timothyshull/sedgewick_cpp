#include "Std_in.h"
#include "Quicksort.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Quicksort::sort(a);
    Quicksort::show(a);
    utility::assert(Quicksort::is_sorted(a), "Quicksort is_sorted check failed");

    Std_random::shuffle(a);

    Std_out::print_line();
    for (int i = 0; i < a.size(); i++) {
        std::string ith = Quicksort::select(a, i);
        Std_out::print_line(ith);
    }
    return 0;
}