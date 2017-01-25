#include "Alphabet.h"
#include "Std_out.h"
#include "Std_in.h"

int main(int argc, char* argv[])
{
    Alphabet alphabet{argv[1]};
    int r = alphabet.radix();
    std::vector<int> count(r);
    while (Std_in::has_next_char()) {
        char c = Std_in::read_char();
        if (alphabet.contains(c)) {
            count[alphabet.to_index(c)] += 1;
        }
    }
    for (int c{0}; c < r; ++c) {
        // TODO: fix this
        Std_out::printf("Count for char %d: %d\n", alphabet.to_char(c), count[c]);
    }
    return 0;
}
