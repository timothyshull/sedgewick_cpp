#include <string>
#include <vector>

#include "Index_binomial_min_pq.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> strings{"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    Index_binomial_min_pq<std::string> pq{static_cast<int>(strings.size())};
    for (int i{0}; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    int i;
    while (!pq.is_empty()) {
        i = pq.delete_min();
        Std_out::print_line(i + " " + strings[i]);
    }
    Std_out::print_line();

    for (i = 0; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    for (auto it = pq.begin(); it != pq.end(); ++it) {
        Std_out::print_line(*it + " " + strings[it->index()]);
    }
    while (!pq.is_empty()) {
        pq.delete_min();
    }

    return 0;
}