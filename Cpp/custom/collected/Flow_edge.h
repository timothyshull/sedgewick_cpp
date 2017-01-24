#ifndef FLOW_EDGE_H
#define FLOW_EDGE_H

#include <string>

class Flow_edge {
public:
    Flow_edge(int v, int w, double capacity);
    Flow_edge(int v, int w, double capacity, double flow);
    Flow_edge(Flow_edge& e);
    int from();
    int to();
    double capacity();
    double flow();
    int other(int vertex);
    double residualCapacityTo(int vertex);
    void addResidualFlowTo(int vertex, double delta);
    std::string to_string();
private:
    const int v;
    const int w;
    const double capacity;
    double flow;
};

std::ostream& operator<<(std::ostream& os, Flow_edge& out);

#endif // FLOW_EDGE_H
