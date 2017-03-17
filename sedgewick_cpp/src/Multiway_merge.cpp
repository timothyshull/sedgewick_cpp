#include "Multiway_merge.h"
#include "Index_min_pq.h"
#include "Std_out.h"

void ::Multiway_merge::merge(std::vector<In>& streams)
{
    auto n = streams.size();
    Index_min_pq<std::string> pq{n};
    for (int i{0}; i < n; ++i) {
        if (!streams[i].is_empty()) {
            pq.insert(i, streams[i].read_string());
        }
    }

    int i;
    while (!pq.is_empty()) {
        Std_out::print(pq.min_key() + " ");
        i = pq.delete_min();
        if (!streams[i].is_empty()) {
            pq.insert(i, streams[i].read_string());
        }
    }
    Std_out::print_line();
}
