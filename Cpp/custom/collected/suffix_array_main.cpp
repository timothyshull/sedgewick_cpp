#include <string>
#include "Std_out.h"
#include "Std_in.h"
#include "utility.h"
#include "Suffix_array.h"

int main(int argc, char* argv[])
{
    std::string s = Std_in::read_all().replaceAll("\\s+", " ").trim();
    Suffix_array suffix{s};

    // Std_out::print_line("rank(" + argv[1] + ") = " + suffix.rank(argv[1]));

    Std_out::print_line("  i ind lcp rnk select");
    Std_out::print_line("---------------------------");

    for (int i{0}; i < s.length(); ++i) {
        int index = suffix.index(i);
        std::string ith = "\"" + s.substr(index, std::min(index + 50, s.length())) + "\"";
        utility::alg_assert(s.substr(index).equals(suffix.select(i));
        int rank = suffix.rank(s.substr(index));
        if (i == 0) {
            Std_out::printf("%3d %3d %3s %3d %s\n", i, index, "-", rank, ith);
        } else {
            int lcp = suffix.lcp(i);
            Std_out::printf("%3d %3d %3d %3d %s\n", i, index, lcp, rank, ith);
        }
    }
    return 0;
}