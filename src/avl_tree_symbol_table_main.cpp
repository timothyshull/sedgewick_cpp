#include <iostream>
#include <vector>

#include "AVL_tree_symbol_table.h"
#include "Std_in.h"

int main()
{
    auto st = AVL_tree_symbol_table<std::string, int>{};
    auto vs = Std_in::read_all_strings();

    for (auto i = 0; i < vs.size(); ++i) {
        st.put(vs[i], i);
    }

    for (auto const &s : st.keys()) {
        try {
            auto v = st.get(s);
            Std_out::printf("Key: %s, value: %d\n", s.c_str(), v);
        } catch (...) {
            Std_out::print_line("threw");
        }
    }
    Std_out::print_line();
    return 0;
}
