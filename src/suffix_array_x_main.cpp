#include <string>
#include "Std_out.h"
#include "utility.h"
#include "Suffix_array_x.h"
#include "Suffix_array.h"

int main(int argc, char* argv[])
{
    std::string s{Std_in::readAll().replaceAll("\n", " ").trim()};
    Suffix_array_x suffix1{s};
    Suffix_array suffix2{s};
    bool check{true};
    for (auto i = 0; check && i < s.length(); ++i) {
        if (suffix1._index(i) != suffix2.index(i)) {
            Std_out::print_line("suffix1(" + i + ") = " + suffix1._index(i));
            Std_out::print_line("suffix2(" + i + ") = " + suffix2.index(i));
            std::string ith = "\"" + s.substring(suffix1._index(i), std::min(suffix1._index(i) + 50, s.length())) + "\"";
            std::string jth = "\"" + s.substring(suffix2.index(i), std::min(suffix2.index(i) + 50, s.length())) + "\"";
            Std_out::print_line(ith);
            Std_out::print_line(jth);
            check = false;
        }
    }

    Std_out::print_line("  i ind lcp rnk  select");
    Std_out::print_line("---------------------------");

    for (auto i = 0; i < s.length(); ++i) {
        int index = suffix2.index(i);
        std::string ith = "\"" + s.substr(index, std::min(index + 50, s.length())) + "\"";
        int rank = suffix2.rank(s.substr(index));
        utility::alg_assert(s.substr(index).equals(suffix2.select(i));
        if (i == 0) {
            Std_out::printf("%3d %3d %3s %3d  %s\n", i, index, "-", rank, ith);
        } else {
            // int lcp  = suffix.lcp(suffix2.index(i), suffix2.index(i-1));
            int lcp = suffix2.lcp(i);
            Std_out::printf("%3d %3d %3d %3d  %s\n", i, index, lcp, rank, ith);
        }
    }
    return 0;
}