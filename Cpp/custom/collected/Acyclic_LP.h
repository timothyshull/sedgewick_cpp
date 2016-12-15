#ifndef COLLECTED_ACYCLICLP_H
#define COLLECTED_ACYCLICLP_H

#include<type_traits>
#include<vector>

template<class T, class Enable = void>
class Acyclic_LP {};

template<typename Float_type>
class Acyclic_LP<Float_type, typename std::enable_if<std::is_floating_point<Float_type>::value>::type> {
    std::vector<Float_type> distance_to;
    std::vector<Directed_edge> edge_to;

    void relax(Directed_edge &e) {
        int v = e.from();
        int w = e.to();
        if (distance_to[w] < distance_to[v] + e.weight()) {
            distance_to[w] = distance_to[v] + e.weight();
            edge_to[w] = e;
        }
    }

public:
    Acyclic_LP(Edge_weighted_digraph &g, std::size_t size) : distance_to{std::vector<Float_type>(g.num_vertices())}, edge_to{std::vector<Directed_edge>(g.num_vertices())}  {
        for (int v = 0; v < g.num_vertices(); v++) {
            distance_to[v] = std::numeric_limits<Float_type>::infinity();
        }
        distance_to[size] = 0.0;

        Topological topological{g};

        if (!topological.has_order()) {
            throw std::invalid_argument{"Digraph is not acyclic."};
        }

        for (auto v : topological.order()) {
            for (auto e : g.adjacent(v)) {
                relax(e);
            }
        }
    }

    inline Float_type get_distance_to(int v) { return distance_to[v]; }

    inline bool has_path_to(int v) { return distance_to[v] < std::numeric_limits<Float_type>::infinity(); }

    Stack<Directed_edge> path_to(int v) {
        Stack<Directed_edge> path;
        if (!has_path_to(v)) {
            return path;
        }
        for (Directed_edge e = edge_to[v]; ; e = edge_to[e.from()]) {
            path.push(e);
        }
        return path;
    }
};

#endif //COLLECTED_ACYCLICLP_H
