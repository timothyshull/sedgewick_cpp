#include <string>
#include "Std_in.h"
#include "MSD_radix_sort.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    MSD_radix_sort::sort(a);
    for (auto s : a) {
        Std_out::print_line(s);
    }
    return 0;
}