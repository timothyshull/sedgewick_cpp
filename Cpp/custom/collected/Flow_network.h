#ifndef FLOW_NETWORK_H
#define FLOW_NETWORK_H

#include <vector>
#include "Flow_edge.h"
#include "In.h"

class Flow_network {
public:
    Flow_network(int V);
    Flow_network(int V, int E);
    Flow_network(In& in);
    int V();
    int E();
    void addEdge(Flow_edge& e);
    std::vector<Flow_edge> adj(int v);
    std::vector<Flow_edge> edges();
    std::string toString();
private:
    const int V;
    int E;
    std::vector<std::vector<Flow_edge>> adj;
    void validateVertex(int v);
};

std::ostream& operator<<(std::ostream& os, Flow_network& out);

#endif // FLOW_NETWORK_H
