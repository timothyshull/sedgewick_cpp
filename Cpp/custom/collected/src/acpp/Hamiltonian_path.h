// Program 17.17 - Hamilton path
#ifndef HAMILTONIAN_PATH_H
#define HAMILTONIAN_PATH_H

#include <vector>

template<typename Graph_type>
class Hamiltonian_path {
public:
    Hamiltonian_path(const Graph_type& graph, int source, int destination, int distance)
            : _graph{graph},
              _visited(graph.num_vertices(), false) { _found = _search_r(source, destination, distance); }

    inline bool exists() const noexcept { return _found; }

private:
    const Graph_type& _graph;
    std::vector<bool> _visited;
    bool _found;

    bool _search_r(int source, int destination, int distance)
    {
        if (source == destination) { return (distance == 0); }
        _visited[source] = true;
        // typename Graph_type::adjIterator A(_graph, source);
        for (auto t : _graph.adjacent(source)) {
            if (!_visited[t]) {
                if (_search_r(t, destination, distance - 1)) { return true; }
            }
        }
        _visited[source] = false;
        return false;
    }
};




#endif // HAMILTONIAN_PATH_H
