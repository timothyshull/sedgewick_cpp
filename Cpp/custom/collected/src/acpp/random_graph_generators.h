#ifndef COLLECTED_RANDOM_GRAPH_GENERATORS_H
#define COLLECTED_RANDOM_GRAPH_GENERATORS_H

static void randE(Graph& G, int E)
{
    for (int i = 0; i < E; i++) {
        int v = int(G.V() * rand() / (1.0 + RAND_MAX));
        int w = int(G.V() * rand() / (1.0 + RAND_MAX));
        G.insert(Edge(v, w));
    }
}

static void randG(Graph& G, int E)
{
    double p = 2.0 * E / G.V() / (G.V() - 1);
    for (int i = 0; i < G.V(); i++) {
        for (int j = 0; j < i; j++) {
            if (rand() < p * RAND_MAX) {
                G.insert(Edge(i, j));
            }
        }
    }
}


#endif // COLLECTED_RANDOM_GRAPH_GENERATORS_H
