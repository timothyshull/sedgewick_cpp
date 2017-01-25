#include <string>
#include "Std_out.h"
#include "In.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    ST <std::string, Set<File>> st{};

    Std_out::print_line("Indexing files");
    for (std::string filename : argv) {
        Std_out::print_line("  " + filename);
        File file{filename};
        In in{file};
        while (!in.is_empty()) {
            std::string word = in.read_string();
            if (!st.contains(word)) { st.put(word, new Set<File>()); }
            Set <File> set = st.get(word);
            set.add(file);
        }
    }

    while (!Std_in::is_empty()) {
        std::string query = Std_in::read_string();
        if (st.contains(query)) {
            Set <File> set = st.get(query);
            for (File file : set) {
                Std_out::print_line("  " + file.getName());
            }
        }
    }
    return 0;
}