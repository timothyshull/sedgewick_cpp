#include <cmath>

#include "Edge.h"
#include "utility.h"

Edge::Edge()
        : _source{-1},
          _destination{-1},
          _weight{std::numeric_limits<double>::infinity()} {}

Edge::Edge(int source, int destination)
        : _source{source},
          _destination{destination},
          _weight{0.0} {}

Edge::Edge(int source, int destination, double weight) : _source{source}, _destination{destination}, _weight{weight}
{
    if (std::isnan(weight)) { throw utility::Illegal_argument_exception{"Weight is NaN"}; }
}

int Edge::other(int vertex)
{
    if (vertex == _source) { return _destination; }
    else if (vertex == _destination) { return _source; }
    else { throw utility::Illegal_argument_exception{"Illegal endpoint"}; }
}

std::ostream& operator<<(std::ostream& os, Edge& out)
{
    return os << out.to_string();
}
