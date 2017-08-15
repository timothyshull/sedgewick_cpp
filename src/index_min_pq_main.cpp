#include <string>
#include <vector>
#include "Index_min_pq.h"
#include "Std_out.h"

int main(int argc, char *argv[]) {
    std::vector<std::string> strings{"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    Index_min_pq<std::string> pq{strings.size()};
    for (auto i = 0; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    while (!pq.is_empty()) {
        int i = pq.delMin();
        Std_out::print_line(i + " " + strings[i]);
    }
    Std_out::print_line();

    for (auto i = 0; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    for (int i : pq) {
        Std_out::print_line(i + " " + strings[i]);
    }
    while (!pq.is_empty()) {
        pq.delMin();
    }
    return 0;
}