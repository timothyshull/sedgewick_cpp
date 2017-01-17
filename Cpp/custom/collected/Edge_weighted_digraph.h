#ifndef COLLECTED_EDGE_WEIGHTED_DIGRAPH_H
#define COLLECTED_EDGE_WEIGHTED_DIGRAPH_H

#include <string>
#include <vector>
#include <istream>
#include <sstream>

#include "Directed_edge.h"
#include "Std_random.h"
#include "Stack.h"

//
class Edge_weighted_digraph {
    static std::string newline = "\n";

    unsigned _num_vertices;
    int _num_edges;
    // Bag<Directed_edge>[] adj;
    // TODO: check edge size and either copy edges or use edge pointers
    std::vector<std::vector<Directed_edge>> _adjacency_lists;
    std::vector<int> _indegree;

    void _validate_vertex(int v)
    {
        if (v < 0 || v >= _num_vertices) {
            throw utility::Index_out_of_bounds_exception("The vertex is not between 0 and the number of vertices");
        }
    }

public:
    explicit Edge_weighted_digraph(unsigned num_vertices)
            : _num_vertices{num_vertices}, _num_edges{0}, _adjacency_lists(num_vertices), _indegree(num_vertices)
    {
        for (int i = 0; i < _num_vertices; i++) {
            _adjacency_lists[i] = std::vector<Directed_edge>{};
        }
    }

    Edge_weighted_digraph(unsigned num_vertices, unsigned num_edges)
            : _num_vertices{num_vertices}, _num_edges{num_edges}, _adjacency_lists(num_vertices), _indegree(num_vertices)
    {
        int v;
        int w;
        double weight;
        for (int i = 0; i < _num_edges; i++) {
            v = Std_random::uniform(_num_vertices);
            w = Std_random::uniform(_num_vertices);
            weight = 0.01 * Std_random::uniform(100);
            Directed_edge e{v, w, weight};
            add_edge(e);
        }
    }

    Edge_weighted_digraph(std::istream& in)
    {
        int num_vertices;
        in >> num_vertices;
        *this = Edge_weighted_digraph(num_vertices);
        int num_edges;
        in >> num_edges;
        if (num_edges < 0) {
            throw utility::Index_out_of_bounds_exception("Number of edges must be non-negative");
        }

        int v;
        int w;
        for (int i = 0; i < num_edges; ++i) {
            in >> v;
            in >> w;

            if (v < 0 || v >= num_vertices || w < 0 || w >= num_vertices) {
                throw utility::Index_out_of_bounds_exception("The vertex must be between 0 and the number of vertices - 1");
            }
            double weight;
            in >> weight;
            Directed_edge e{v, w, weight};
            add_edge(e);
        }
    }

    Edge_weighted_digraph(const Edge_weighted_digraph& g)
            : _num_vertices{g._num_vertices}, _num_edges{g._num_edges}, _indegree{g._indegree}
    {
        for (int v = 0; v < _num_vertices; ++v) {
            Stack<Directed_edge> reverse;
            for (auto e : g._adjacency_lists[v]) {
                reverse.push(e);
            }
            for (auto e : reverse) {
                _adjacency_lists[v].emplace_back(e);
            }
        }
    }

    inline int num_vertices() const { return _num_vertices; }

    inline int num_edges() const { return _num_edges; }

    void add_edge(Directed_edge& e)
    {
        int v = e.from();
        int w = e.to();
        _validate_vertex(v);
        _validate_vertex(w);
        _adjacency_lists[v].emplace_back(e);
        _indegree[w] += 1;
        ++_num_edges;
    }

    std::vector<Directed_edge> adjacent(int v)
    {
        _validate_vertex(v);
        return _adjacency_lists[v];
    }

    int outdegree(int v)
    {
        _validate_vertex(v);
        return _adjacency_lists[v].size();
    }

    int indegree(int v)
    {
        _validate_vertex(v);
        return _indegree[v];
    }

    std::vector<Directed_edge> get_edges()
    {
        std::vector<Directed_edge> v;
        for (auto v : _adjacency_lists) {
            for (auto e : v) {
                v.emplace_back(e);
            }
        }
        return v;
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "Edge_weighted_digraph(\n    number of vertices: " << _num_vertices << ",\n    number of edges: " << _num_edges << "\n";
        for (int v = 0; v < _num_vertices; ++v) {
            ss << "    edges for vertex v: ";
            for (auto e : _adjacency_lists[v]) {
                ss << e << ", ";
            }
            ss << "\n";
        }
        return ss.str();
    }

};

#endif //COLLECTED_EDGE_WEIGHTED_DIGRAPH_H
