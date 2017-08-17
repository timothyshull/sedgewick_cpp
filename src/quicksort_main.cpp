#include "Std_in.h"
#include "Quicksort.h"

int main()
{
    auto strings = Std_in::read_all_strings();
    Quicksort::sort(strings);
    Quicksort::show(strings);

    Std_random::shuffle(strings);

    Std_out::print_line();
    for (auto i = 0; i < strings.size(); ++i) {
        auto ith = Quicksort::select(strings, i);
        Std_out::print_line(ith);
    }
    return 0;
}