#ifndef COLLECTED_HAMILTONIAN_PATH_H
#define COLLECTED_HAMILTONIAN_PATH_H

template<typename Graph_type>
class Hamiltonian_path {
    const Graph_type& G;
    vector<bool> visited;
    bool found;

    bool searchR(int v, int w, int d)
    {
        if (v == w) { return (d == 0); }
        visited[v] = true;
        typename Graph_type::adjIterator A(G, v);
        for (int t = A.beg(); !A.end(); t = A.nxt()) {
            if (!visited[t]) {
                if (searchR(t, w, d - 1)) { return true; }
            }
        }
        visited[v] = false;
        return false;
    }

public:
    Hamiltonian_path(const Graph_type& G, int v, int w) :
            G(G), visited(G.V(), false) { found = searchR(v, w); }

    bool exists() const { return found; }
};




#endif // COLLECTED_HAMILTONIAN_PATH_H
