#ifndef TRANSITIVE_CLOSURE_WARSHALL_H
#define TRANSITIVE_CLOSURE_WARSHALL_H

template<typename tcGraph, typename Graph> class TC {
    tcGraph T;
public:
    TC(const Graph& G) : T(G)
    {
        for (int s = 0; s < T.V(); s++) {
            T.insert(Edge(s, s));
        }
        for (int i = 0; i < T.V(); i++) {
            for (int s = 0; s < T.V(); s++) {
                if (T.edge(s, i)) {
                    for (int t = 0; t < T.V(); t++) {
                        if (T.edge(i, t)) {
                            T.insert(Edge(s, t));
                        }
                    }
                }
            }
        }
    }

    bool reachable(int s, int t) const { return T.edge(s, t); }
};



#endif // TRANSITIVE_CLOSURE_WARSHALL_H
