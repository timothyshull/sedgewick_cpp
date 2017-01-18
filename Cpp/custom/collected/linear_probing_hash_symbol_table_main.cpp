#include "Linear_probing_hash_symbol_table.h"
#include "Std_in.h"
#include "Std_out.h"

int main()
{
    Linear_probing_hash_symbol_table<std::string, int> st;
    int i{0};
    std::string key;
    while (!Std_in::is_empty()) {
        key = Std_in::read_string();
        st.put(key, i);
        ++i;
    }

    for (auto s : st.keys()) {
        std::stringstream ss;
        ss << s << " " << *st.get(s);
        Std_out::print_line(ss.str());
    }
    return 0;
}