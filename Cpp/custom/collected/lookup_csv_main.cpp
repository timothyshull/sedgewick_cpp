#include "Symbol_table.h"
#include "In.h"
#include "Std_in.h"
#include "Std_out.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    int key_field{utility::str_to_num(argv[1])};
    int value_field{utility::str_to_num(argv[2])};

    Symbol_table<std::string, std::string> st;

    In in{argv[1]};
    while (in.hasNextLine()) {
        std::string line{in.read_line()};
        std::vector<std::string> tokens;
        utility::split_string(line, ',', tokens);
        std::string key = tokens[key_field];
        std::string val = tokens[value_field];
        st.put(key, val);
    }

    while (!Std_in::is_empty()) {
        std::string s = Std_in::read_string();
        if (st.contains(s)) { Std_out::print_line(st.get(s)); }
        else { Std_out::print_line("Not found"); }
    }
    return 0;
}