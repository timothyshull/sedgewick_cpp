#ifndef SIMPLE_PATH_SEARCH_H
#define SIMPLE_PATH_SEARCH_H

template<typename Graph> class Hamiltonian_path {
    const Graph& _graph;
    vector<bool> _visited;
    bool _found;

    bool searchR(int v, int w)
    {
        if (v == w) { return true; }
        _visited[v] = true;
        typename Graph::adjIterator A(_graph, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!_visited[t]) {
                if (searchR(t, w)) { return true; }
            }
        }
        return false;
    }

public:
    Hamiltonian_path(const Graph& G, int v, int w) :
            _graph(G), _visited(G.V(), false) { _found = searchR(v, w); }

    bool exists() const { return _found; }
};

#endif // SIMPLE_PATH_SEARCH_H
