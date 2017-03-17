#include "Flow_edge.h"
#include "utility.h"

Flow_edge::Flow_edge(int v, int w, double capacity)
        : _v{v},
          _w{w},
          _capacity{capacity},
          _flow{0.0}
{
    if (v < 0) { throw utility::Index_out_of_bounds_exception{"Vertex name must be a non-negative integer"}; }
    if (w < 0) { throw utility::Index_out_of_bounds_exception{"Vertex name must be a non-negative integer"}; }
    if (capacity < 0.0) { throw utility::Illegal_argument_exception{"Edge capacity must be non-negative"}; }
}

Flow_edge::Flow_edge(int v, int w, double capacity, double flow)
        : _v{v},
          _w{w},
          _capacity{capacity},
          _flow{flow}
{
    if (v < 0) { throw utility::Index_out_of_bounds_exception{"Vertex name must be a non-negative integer"}; }
    if (w < 0) { throw utility::Index_out_of_bounds_exception{"Vertex name must be a non-negative integer"}; }
    if (capacity < 0.0) { throw utility::Illegal_argument_exception{"Edge capacity must be non-negative"}; }
    if (flow > capacity) { throw utility::Illegal_argument_exception{"Flow exceeds capacity"}; }
    if (flow < 0.0) { throw utility::Illegal_argument_exception{"Flow must be non-negative"}; }
}

int Flow_edge::other(int vertex)
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
}

double Flow_edge::residual_capacity_to(int vertex)
{
    if (vertex == _v) {
        return _flow;
    } else if (vertex == _w) {
        return _capacity - _flow;
    } else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
}

void Flow_edge::add_residual_flow_to(int vertex, double delta)
{
    if (vertex == _v) {
        _flow -= delta;
    } else if (vertex == _w) {
        _flow += delta;
    } else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
    if (std::isnan(delta)) { throw utility::Illegal_argument_exception{"Change _in flow = NaN"}; }
    if (_flow < 0.0) { throw utility::Illegal_argument_exception{"Flow is negative"}; }
    if (_flow > _capacity) { throw utility::Illegal_argument_exception{"Flow exceeds capacity"}; }
}

std::string Flow_edge::to_string()
{
    std::stringstream ss;
    ss << "Flow_edge(source: " << _v << ", destination: " << _w << ", flow: " << _flow << ", capacity: " << _capacity << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, Flow_edge& out)
{
    return os << out.to_string();
}