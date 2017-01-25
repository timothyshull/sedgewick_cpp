#include "Std_out.h"
#include "Symbol_table.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Symbol_table<std::string, int> st{};
    for (int i = 0; !Std_in::is_empty(); ++i) {
        std::string key = Std_in::read_string();
        st.put(key, i);
    }
    for (auto s : st.keys()) {
        Std_out::print_line(s + " " + st.get(s));
    }
    return 0;
}