#include <iostream>
#include <vector>

#include "AVL_tree_symbol_table.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    AVL_tree_symbol_table<std::string, int> st;
    std::vector<std::string> vs = Std_in::read_all_strings();

    for (auto i = 0; i < vs.size(); ++i) {
        st.put(vs[i], i);
    }

    for (auto s : st.keys()) {
        Std_out::printf("Key: %s, value: %d\n", s.c_str(), *st.get(s));
    }
    Std_out::print_line();
    return 0;
}
