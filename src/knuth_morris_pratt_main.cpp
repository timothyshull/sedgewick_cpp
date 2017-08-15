#include "Knuth_morris_pratt.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string pat{argv[1]};
    std::string txt{argv[2]};

    std::vector<char> pattern;
    pattern.reserve(pat.size());
    for (auto i = 0; i < pat.size(); ++i) {
        pattern.emplace_back(pat[i]);
    }

    std::vector<char> text;
    text.reserve(txt.size());
    for (auto i = 0; i < txt.size(); ++i) {
        pattern.emplace_back(txt[i]);
    }

    Knuth_morris_pratt kmp1{pat};
    int offset1 = kmp1.search(txt);

    Knuth_morris_pratt kmp2{pattern, 256};
    int offset2 = kmp2.search(text);

    Std_out::print_line("text:    " + txt);

    Std_out::print("pattern: ");
    for (auto i = 0; i < offset1; ++i) {
        Std_out::print(" ");
    }
    Std_out::print_line(pat);

    Std_out::print("pattern: ");
    for (auto i = 0; i < offset2; ++i) {
        Std_out::print(" ");
    }
    Std_out::print_line(pat);
    return 0;
}