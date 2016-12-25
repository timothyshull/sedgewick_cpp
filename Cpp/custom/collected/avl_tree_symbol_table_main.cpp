#include<iostream>

#include "AVL_tree_symbol_table.h"

int main() {
    AVL_tree_symbol_table<std::string, int> st{};

    std::string line;
    for (int i = 0; std::getline(std::cin, line) && line != ""; i++) {
        st.put(line, i);
    }

    for (auto s : st.keys()) {
        std::cout << " " << st.get(s) << "\n";
    }
    std::cout << "\n";
    return 0;
}
