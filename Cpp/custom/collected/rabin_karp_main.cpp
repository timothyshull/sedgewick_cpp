#include <string>
#include "Rabin_karp.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::string pat{argv[1]};
    std::string txt{argv[2]};

    Rabin_karp searcher{pat};
    int offset{searcher.search(txt)};

    Std_out::print_line("text:    " + txt);

    Std_out::print("pattern: ");
    for (int i = 0; i < offset; ++i) {
        Std_out::print(" ");
    }
    Std_out::print_line(pat);
    return 0;
}