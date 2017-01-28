#include <string>
#include <fstream>
#include "Std_out.h"
#include "In.h"
#include "Set.h"
#include "Std_in.h"
#include "Symbol_table.h"

int main(int argc, char* argv[])
{
    Symbol_table <std::string, Set<std::ifstream>> st;

    std::vector<std::string> args;
    args.reserve(static_cast<std::vector<std::string>::size_type>(argc));

    for (int i{0}; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }

    Std_out::print_line("Indexing files");
    for (std::string filename : args) {
        Std_out::print_line("  " + filename);
        std::ifstream file{filename};
        In in{file};
        while (!in.is_empty()) {
            std::string word = in.read_string();
            if (!st.contains(word)) { st.put(word, Set<std::ifstream>()); }
            Set <std::ifstream> set = st.get(word);
            set.add(file);
        }
    }

    while (!Std_in::is_empty()) {
        std::string query = Std_in::read_string();
        if (st.contains(query)) {
            Set <std::ifstream> set = st.get(query);
            for (auto file : set) {
                Std_out::print_line("  " + file.getName());
            }
        }
    }
    return 0;
}