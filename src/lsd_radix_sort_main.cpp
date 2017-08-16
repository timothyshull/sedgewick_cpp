#include <string>
#include "Std_in.h"
#include "utility.h"
#include "LSD_radix_sort.h"

int main()
{
    auto strings = Std_in::read_all_strings();
    auto str_sz = strings[0].size();
    for (auto const &s : strings) {
        utility::alg_assert(s.size() == str_sz, "strings must have fixed length");
    }

    LSD_radix_sort::sort(strings, static_cast<int>(str_sz));
    LSD_radix_sort::show(strings);
    return 0;
}