#include "TST.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    TST<int> st{};
    for (auto i = 0; !Std_in::is_empty(); i++) {
        std::string key{Std_in::read_string()};
        st.put(key, i);
    }

    if (st.size() < 100) {
        Std_out::print_line("keys(\"\"):");
        for (auto key : st.keys()) {
            Std_out::print_line(key + " " + st.get(key));
        }
        Std_out::print_line();
    }

    Std_out::print_line("longestPrefixOf(\"shellsort\"):");
    Std_out::print_line(st.longestPrefixOf("shellsort"));
    Std_out::print_line();

    Std_out::print_line("longestPrefixOf(\"shell\"):");
    Std_out::print_line(st.longestPrefixOf("shell"));
    Std_out::print_line();

    Std_out::print_line("keysWithPrefix(\"shor\"):");
    for (auto s : st.keys_with_prefix("shor")) {
        Std_out::print_line(s);
    }
    Std_out::print_line();

    Std_out::print_line("keysThatMatch(\".he.l.\"):");
    for (auto s : st.keys_that_match(".he.l.")) {
        Std_out::print_line(s);
    }
    return 0;
}