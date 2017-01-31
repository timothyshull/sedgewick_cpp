#include "Alphabet.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Alphabet alphabet{argv[1]};
    int r{alphabet.radix()};
    std::vector<int> count;
    count.reserve(static_cast<std::vector<int>::size_type>(r));

    char c;
    while (Std_in::has_next_char()) {
        c = Std_in::read_char();
        if (alphabet.contains(c)) {
            count[alphabet.to_index(c)] += 1;
        }
    }

    std::stringstream ss;
    for (int i{0}; i < r; ++i) {
        ss.str("");
        ss << "Count for char " << alphabet.to_char(i) << ": " << count[i];
        Std_out::print_line(ss.str());
    }
    return 0;
}
