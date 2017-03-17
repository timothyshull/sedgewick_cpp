#include <string>
#include <vector>
#include "Boyer_moore.h"
#include "Std_out.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    std::string pat{argv[1]};
    std::string txt{argv[2]};
    std::vector<char> pattern{utility::str_to_char_vector(pat)};
    std::vector<char> text{utility::str_to_char_vector(txt)};

    Boyer_moore boyer_moore1{pat};
    Boyer_moore boyer_moore2{pattern, 256};
    int offset1{boyer_moore1.search(txt)};
    int offset2{boyer_moore2.search(text)};

    Std_out::print_line("text:    " + txt);

    Std_out::print("pattern: ");
    for (int i{0}; i < offset1; ++i) {
        Std_out::print(" ");
    }
    Std_out::print_line(pat);

    Std_out::print("pattern: ");
    for (int i{0}; i < offset2; ++i) {
        Std_out::print(" ");
    }
    Std_out::print_line(pat);
    return 0;
}