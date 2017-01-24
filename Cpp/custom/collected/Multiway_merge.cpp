#include "Multiway_merge.h"

void ::Multiway_merge::merge(std::vector<In>& streams)
{
    int n = streams.length;
    IndexMinPQ<String> pq = new IndexMinPQ<String>(n);
    for (int i = 0; i < n; i++)
        if (!streams[i].isEmpty())
            pq.insert(i, streams[i].readString());

    // Extract and print min and read next from its stream.
    while (!pq.isEmpty()) {
        StdOut.print(pq.minKey() + " ");
        int i = pq.delMin();
        if (!streams[i].isEmpty())
            pq.insert(i, streams[i].readString());
    }
    StdOut.println();
}
