#include <string>
#include <vector>
#include "Index_max_pq.h"
#include "Std_out.h"
#include "Std_random.h"

int main(int argc, char* argv[])
{
    std::vector<std::string> strings{"it", "was", "the", "best", "of", "times", "it", "was", "the", "worst"};

    Index_max_pq<std::string> pq{strings.size()};
    for (int i = 0; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    for (auto i : pq) {
        Std_out::print_line(i + " " + strings[i]);
    }

    Std_out::print_line();

    for (int i = 0; i < strings.size(); ++i) {
        if (Std_random::uniform() < 0.5) {
            pq.increaseKey(i, strings[i] + strings[i]);
        } else {
            pq.decreaseKey(i, strings[i].substr(0, 1));
        }
    }

    while (!pq.is_empty()) {
        std::string key = pq.maxKey();
        int i = pq.delMax();
        Std_out::print_line(i + " " + key);
    }
    Std_out::print_line();

    for (int i = 0; i < strings.size(); ++i) {
        pq.insert(i, strings[i]);
    }

    std::vector<int> perm;
    perm.reserve(strings.size());
    for (int i = 0; i < strings.size(); ++i) {
        perm[i] = i;
    }
    Std_random::shuffle(perm);
    for (int i = 0; i < perm.size(); ++i) {
        std::string key = pq.keyOf(perm[i]);
        pq.remove(perm[i]);
        Std_out::print_line(perm[i] + " " + key);
    }
    return 0;
}