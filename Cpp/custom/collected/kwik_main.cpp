#include "In.h"
#include "Std_in.h"
#include "Std_out.h"
#include "Suffix_array.h"
#include "utility.h"

int main(int argc, char* argv[])
{
    In in{argv[1]};
    int context = utility::str_to_num(argv[1]);

    std::vector<std::string> all_strings = in.readAllStrings();
    std::stringstream ss;
    for (auto s : all_strings) {
        ss << s << " ";
    }
    std::string text{ss.str()};
    int n{text.length()};

    Suffix_array sa{text};

    int from1;
    int to1;
    int from2;
    int to2;
    while (!Std_in::is_empty()) {
        std::string query = Std_in::read_line();
        for (int i = sa.rank(query); i < n; ++i) {
            from1 = sa.index(i);
            to1 = std::min(n, from1 + query.length());
            if (query != text.substr(from1, to1)) { break; }
            from2 = std::max(0, sa.index(i) - context);
            to2 = std::min(n, sa.index(i) + context + query.length());
            Std_out::print_line(text.substr(from2, to2));
        }
        Std_out::print_line();
    }
    return 0;
}