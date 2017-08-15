#include "Red_black_bst.h"
#include "Std_in.h"

struct String_comparator {
    bool operator()(std::string& x, std::string& y)
    {
        if (x.size() == 0 && y.size() == 0) {
            return 0;
        } else if (x.size() == 0) {
            return -1;
        } else if (y.size() == 0) {
            return 1;
        } else if (x < y) {
            return -1;
        } else if (y < x) {
            return 1;
        }
        return 0;
    }
};

int main()
{
    Red_black_bst<std::string, int, String_comparator> st{};

    auto i = 0;
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