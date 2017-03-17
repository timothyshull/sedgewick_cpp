// Program 17.4 - Graph-processing input/output interface
#ifndef GRAPH_IO_H
#define GRAPH_IO_H

#include <iostream>

#include "Graph_symbol_table.h"

template<typename Graph_type>
class Graph_io {
public:
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

    void simple_scan(Graph_type&);

    void scan(Graph_type& graph)
    {
        std::string v;
        std::string w;
        Graph_symbol_table st;
        while (std::cin >> v >> w) {
            graph.insert(Edge{st.index(v), st.index(w)});
        }
    }

};

#endif // GRAPH_IO_H
