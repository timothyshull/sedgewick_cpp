#include "Std_out.h"
#include "In.h"
#include "Longest_common_substring.h"

int main(int argc, char *argv[]) {
    In<std::ifstream> in1{argv[1]};
    In<std::ifstream> in2{argv[2]};
    std::string s{in1.read_all().trim().replaceAll("\\s+", " ")};
    std::string t{in2.read_all().trim().replaceAll("\\s+", " ")};
    Std_out::print_line("'" + Longest_common_substring::lcs(s, t) + "'");
    return 0;
}