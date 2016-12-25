class SparseMultiGRAPH::adjIterator {
    const SparseMultiGRAPH& G;
    int v;
    link t;
public:
    adjIterator(const SparseMultiGRAPH& G, int v) :
            G(G), v(v) { t = 0; }

    int beg()
    {
        t = G.adj[v];
        return t ? t->v : -1;
    }

    int nxt()
    {
        if (t) { t = t->next; }
        return t ? t->v : -1;
    }

    bool end() { return t == 0; }
};

