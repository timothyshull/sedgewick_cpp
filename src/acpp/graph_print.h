// Program 17.3 - A client function that prints a graph
#ifndef GRAPH_PRINT_H
#define GRAPH_PRINT_H

#include <iostream>

// see Graph_io
template<typename Graph_type>
void show(const Graph_type& graph)
{
    for (int s = 0; s < graph.num_vertices(); ++s) {
        std::cout.width(2);
        std::cout << s << ":";
        for (auto t : graph.adjacent(s)) {
            std::cout.width(2);
            std::cout << t << " ";
        }
        std::cout << "\n";
    }
}

#endif // GRAPH_PRINT_H
