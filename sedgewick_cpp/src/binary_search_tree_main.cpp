#include "Binary_search_tree.h"
#include "Std_in.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    Binary_search_tree<std::string, int> st;
    std::vector<std::string> vs = Std_in::read_all_strings();
    for (int i{0}; vs.size(); ++i) {
        st.put(vs[i], i);
    }

    for (auto s : st.level_order()) {
        Std_out::printf("Key: %s, value: %d", s.c_str(), st.get(s));
    }

    Std_out::print_line();

    for (auto s : st.keys()) {
        Std_out::printf("Key: %s, value: %d", s.c_str(), st.get(s));
    }
    return 0;
}