#include "Std_in.h"
#include "Std_out.h"
#include "Trie_set.h"

int main(int argc, char* argv[])
{
    Trie_set set{};
    while (!Std_in::is_empty()) {
        std::string key = Std_in::read_string();
        set.add(key);
    }

    if (set.size() < 100) {
        Std_out::print_line("keys(\"\"):");
        for (auto key : set) {
            Std_out::print_line(key);
        }
        Std_out::print_line();
    }

    Std_out::print_line("longestPrefixOf(\"shellsort\"):");
    Std_out::print_line(set.longest_prefix_of("shellsort"));
    Std_out::print_line();

    Std_out::print_line("longestPrefixOf(\"xshellsort\"):");
    Std_out::print_line(set.longest_prefix_of("xshellsort"));
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shor\"):");
    for (auto s : set.keys_with_prefix("shor")) {
        Std_out::print_line(s);
    }
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shortening\"):");
    for (auto s : set.keys_with_prefix("shortening")) {
        Std_out::print_line(s);
    }
    Std_out::print_line();

    Std_out::print_line("keysThatMatch(\".he.l.\"):");
    for (auto s : set.keys_that_match(".he.l.")) {
        Std_out::print_line(s);
    }
    return 0;
}