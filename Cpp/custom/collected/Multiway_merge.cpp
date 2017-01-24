#include "Multiway_merge.h"

void ::Multiway_merge::merge(std::vector<In>& streams)
{
    int n = streams.length;
    IndexMinPQ<std::string> pq = new IndexMinPQ<std::string>(n);
    for (int i = 0; i < n; ++i)
        if (!streams[i].is_empty())
            pq.insert(i, streams[i].read_string());

    // Extract and print min and read next from its stream.
    while (!pq.is_empty()) {
        Std_out::print(pq.minKey() + " ");
        int i = pq.delMin();
        if (!streams[i].is_empty())
            pq.insert(i, streams[i].read_string());
    }
    Std_out::print_line();
}
