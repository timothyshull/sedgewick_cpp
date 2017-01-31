#include <string>
#include "Std_in.h"
#include "utility.h"
#include "LSD_radix_sort.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> a{Std_in::read_all_strings()};
    auto w = a[0].size();
    for (auto s : a) {
        utility::alg_assert(s.size() == w, "Strings must have fixed length");
    }

    LSD_radix_sort::sort(a, static_cast<int>(w));

    for (auto s : a) {
        Std_out::print_line(s);
    }
    return 0;
}