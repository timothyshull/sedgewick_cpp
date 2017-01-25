#include <cstdlib>
#include <vector>
#include "Counter.h"
#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int n = utility::str_to_num(argv[1]);
    int trials = utility::str_to_num(argv[2]);

    // create _size counters
    std::vector<Counter> hits(n);
    for (int i{0}; i < n; ++i) {
        std::stringstream ss;
        ss << "Counter: " << i;
        auto s = ss.str();
        hits[i] = Counter(s);
    }

    // increment trials counters at uniform
    for (int t{0}; t < trials; ++t) {
        hits[Std_random::uniform(n)].increment();
    }

    // print results
    for (int i{0}; i < n; ++i) {
        Std_out::print_line(hits[i]);
    }
    return 0;
}
