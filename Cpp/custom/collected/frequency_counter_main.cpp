#include "Std_in.h"
#include "Symbol_table.h"
#include "Std_out.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    int distinct{0};
    int words{0};
    int min_length{utility::str_to_num(argv[1])};
    Symbol_table<std::string, int> st{};

    while (!Std_in::is_empty()) {
        std::string key = Std_in::read_string();
        if (key.length() < min_length) { continue; }
        ++words;
        if (st.contains(key)) {
            st.put(key, st.get(key) + 1);
        } else {
            st.put(key, 1);
            ++distinct;
        }
    }

    std::string max = "";
    st.put(max, 0);
    for (auto word : st.keys()) {
        if (st.get(word) > st.get(max)) {
            max = word;
        }
    }

    Std_out::print_line(max + " " + st.get(max));
    Std_out::print_line("distinct = " + distinct);
    Std_out::print_line("words    = " + words);
    return 0;
}