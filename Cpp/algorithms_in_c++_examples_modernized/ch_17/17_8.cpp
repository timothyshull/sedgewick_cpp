class DenseGRAPH::adjIterator {
    const DenseGRAPH& G;
    int i, v;
public:
    adjIterator(const DenseGRAPH& G, int v) :
            G(G), v(v), i(-1) {}

    int beg()
    {
        i = -1;
        return nxt();
    }

    int nxt()
    {
        for (i++; i < G.V(); i++) {
            if (G.adj[v][i] == true) { return i; }
        }
        return -1;
    }

    bool end() { return i >= G.V(); }
};

