#include <string>
#include "Std_out.h"
#include "Std_in.h"
#include "Longest_repeated_substring.h"

int main(int argc, char *argv[]) {
    std::string text{Std_in::read_all().replaceAll("\\s+", " ")};
    Std_out::print_line("'" + Longest_repeated_substring::lrs(text) + "'");
    return 0;
}