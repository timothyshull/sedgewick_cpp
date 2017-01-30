#include "Std_out.h"
#include "In.h"
#include "Longest_common_substring.h"

int main(int argc, char *argv[]) {
    In in1{argv[1]};
    In in2{argv[2]};
    std::string s{in1.readAll().trim().replaceAll("\\s+", " ")};
    std::string t{in2.readAll().trim().replaceAll("\\s+", " ")};
    Std_out::print_line("'" + Longest_common_substring::lcs(s, t) + "'");
    return 0;
}