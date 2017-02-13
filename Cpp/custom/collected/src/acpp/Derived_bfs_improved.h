#ifndef COLLECTED_DERIVED_BFS_IMPROVED_H
#define COLLECTED_DERIVED_BFS_IMPROVED_H


#include "QUEUE.cc"

template<class Graph>
class BFS : public SEARCH<Graph> {
    vector<int> st;

    void searchC(Edge e)
    {
        QUEUE <Edge> Q;
        Q.put(e);
        ord[e.w] = cnt++;
        while (!Q.empty()) {
            e = Q.get();
            st[e.w] = e.v;
            typename Graph::adjIterator A(G, e.w);
            for (int t = A.beg(); !A.end(); t = A.nxt()) {
                if (ord[t] == -1) {
                    Q.put(Edge(e.w, t));
                    ord[t] = cnt++;
                }
            }
        }
    }

public:
    BFS(Graph& G) : SEARCH<Graph>(G), st(G.V(), -1) { search(); }

    int ST(int v) const { return st[v]; }
};





#endif // COLLECTED_DERIVED_BFS_IMPROVED_H
