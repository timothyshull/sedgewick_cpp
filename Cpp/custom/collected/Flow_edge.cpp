#include "Flow_edge.h"

Flow_edge::Flow_edge(int v, int w, double capacity)
{
    if (v < 0) { throw new IndexOutOfBoundsException("Vertex name must be a non-negative integer"); }
    if (w < 0) { throw new IndexOutOfBoundsException("Vertex name must be a non-negative integer"); }
    if (!(capacity >= 0.0)) { throw utility::Illegal_argument_exception("Edge capacity must be non-negative"); }
    this.v = v;
    this.w = w;
    this.capacity = capacity;
    this.flow = 0.0;
}

Flow_edge::Flow_edge(int v, int w, double capacity, double flow)
{
    if (v < 0) { throw new IndexOutOfBoundsException("Vertex name must be a non-negative integer"); }
    if (w < 0) { throw new IndexOutOfBoundsException("Vertex name must be a non-negative integer"); }
    if (!(capacity >= 0.0)) { throw utility::Illegal_argument_exception("Edge capacity must be non-negative"); }
    if (!(flow <= capacity)) { throw utility::Illegal_argument_exception("Flow exceeds capacity"); }
    if (!(flow >= 0.0)) { throw utility::Illegal_argument_exception("Flow must be non-negative"); }
    this.v = v;
    this.w = w;
    this.capacity = capacity;
    this.flow = flow;
}

Flow_edge::Flow_edge(Flow_edge& e)
{
    this.v = e.v;
    this.w = e.w;
    this.capacity = e.capacity;
    this.flow = e.flow;
}

int Flow_edge::from()
{
    return v;
}

int Flow_edge::to()
{
    return w;
}

double Flow_edge::capacity()
{
    return capacity;
}

double Flow_edge::flow()
{
    return flow;
}

int Flow_edge::other(int vertex)
{
    if (vertex == v) { return w; }
    else if (vertex == w) { return v; }
    else { throw utility::Illegal_argument_exception("Illegal endpoint"); }
}

double Flow_edge::residualCapacityTo(int vertex)
{
    if (vertex == v) {
        return flow;              // backward edge
    } else if (vertex == w) {
        return capacity - flow;   // forward edge
    } else { throw utility::Illegal_argument_exception("Illegal endpoint"); }
}

void Flow_edge::addResidualFlowTo(int vertex, double delta)
{
    if (vertex == v) {
        flow -= delta;           // backward edge
    } else if (vertex == w) {
        flow += delta;           // forward edge
    } else { throw utility::Illegal_argument_exception("Illegal endpoint"); }
    if (Double.isNaN(delta)) { throw utility::Illegal_argument_exception("Change in flow = NaN"); }
    if (!(flow >= 0.0)) { throw utility::Illegal_argument_exception("Flow is negative"); }
    if (!(flow <= capacity)) { throw utility::Illegal_argument_exception("Flow exceeds capacity"); }
}

std::string Flow_edge::to_string()
{
    return v + "->" + w + " " + flow + "/" + capacity;
}

std::ostream& operator<<(std::ostream& os, Flow_edge& out)
{
    return os << out.to_string();
}