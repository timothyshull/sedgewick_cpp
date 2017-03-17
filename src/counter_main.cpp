#include <cstdlib>
#include <vector>
#include "Counter.h"
#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int n{utility::str_to_num(argv[1])};
    int trials{utility::str_to_num(argv[2])};

    std::vector<Counter> hits;
    hits.reserve(static_cast<std::vector<Counter>::size_type>(n));

    for (int i{0}; i < n; ++i) {
        std::string s{"Counter: " + std::to_string(i)};
        hits[i] = Counter{s};
    }

    for (int t{0}; t < trials; ++t) {
        hits[Std_random::uniform(n)].increment();
    }

    for (auto c : hits) {
        Std_out::print_line(c);
    }
    return 0;
}
