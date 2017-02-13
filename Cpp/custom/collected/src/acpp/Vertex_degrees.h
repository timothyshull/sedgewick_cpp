#ifndef COLLECTED_VERTEX_DEGREES_H
#define COLLECTED_VERTEX_DEGREES_H

template<typename Graph> class Vertex_degrees {
    const Graph& G;
    vector<int> degree;
public:
    Vertex_degrees(const Graph& G) : G(G), degree(G.V(), 0)
    {
        for (int v = 0; v < G.V(); v++) {
            typename Graph::adjIterator A(G, v);
            for (int w = A.beg(); !A.end(); w = A.nxt()) {
                degree[v]++;
            }
        }
    }

    int operator[](int v) const { return degree[v]; }
};

#endif // COLLECTED_VERTEX_DEGREES_H
