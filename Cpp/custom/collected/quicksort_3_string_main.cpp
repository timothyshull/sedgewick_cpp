#include "Std_in.h"
#include "Quicksort_3_string.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    Quicksort_3_string::sort(a);
    for (auto s : a) {
        Std_out::print_line(s);
    }
    return 0;
}