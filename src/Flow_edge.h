#ifndef FLOW_EDGE_H
#define FLOW_EDGE_H

#include <string>

class Flow_edge {
public:
    Flow_edge() = default;

    Flow_edge(const Flow_edge&) = default;

    Flow_edge(Flow_edge&&) = default;

    ~Flow_edge() = default;

    Flow_edge& operator=(const Flow_edge&) = default;

    Flow_edge& operator=(Flow_edge&&) = default;

    Flow_edge(int v, int w, double capacity);

    Flow_edge(int v, int w, double capacity, double flow);

    inline int from() const noexcept { return _v; }

    inline int to() const noexcept { return _w; }

    inline double capacity() const noexcept { return _capacity; }

    inline double flow() const noexcept { return _flow; }

    int other(int vertex);

    double residual_capacity_to(int vertex);

    void add_residual_flow_to(int vertex, double delta);

    std::string to_string();

private:
    const int _v;
    const int _w;
    const double _capacity;
    double _flow;
};

std::ostream& operator<<(std::ostream& os, Flow_edge& out);

#endif // FLOW_EDGE_H
