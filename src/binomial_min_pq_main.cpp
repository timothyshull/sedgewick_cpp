#include "Std_out.h"
#include "Binomial_min_pq.h"
#include "Std_in.h"

int main()
{
    auto pq = Binomial_min_pq<std::string>{};
    while (!Std_in::is_empty()) {
        auto item = Std_in::read_string();
        if (item != "-") {
            pq.insert(item);
        } else if (!pq.is_empty()) {
            Std_out::print_line(pq.delete_min() + " ");
        }
    }
    Std_out::print_line("(" + std::to_string(pq.size()) + " left on priority queue)");
    return 0;
}