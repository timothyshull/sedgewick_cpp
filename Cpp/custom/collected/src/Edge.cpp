#include <cmath>

#include "Edge.h"
#include "utility.h"

Edge::Edge(int v, int w, double weight) : _v{v}, _w{w}, _weight{weight}
{
    if (std::isnan(weight)) { throw utility::Illegal_argument_exception{"Weight is NaN"}; }
}

int Edge::other(int vertex)
{
    if (vertex == _v) { return _w; }
    else if (vertex == _w) { return _v; }
    else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
}

std::ostream& operator<<(std::ostream& os, Edge& out)
{
    return os << out.to_string();
}
