#include <sstream>
#include <iomanip>
#include "Directed_edge.h"

Directed_edge::Directed_edge(int source, int destination, double weight) : _source{source}, _destination{destination}, _weight{weight}
{
    if (source < 0) {
        throw utility::Index_out_of_bounds_exception("Vertex names must be non-negative integers");
    }
    if (destination < 0) {
        throw utility::Index_out_of_bounds_exception("Vertex names must be non-negative integers");
    }
    if (std::isnan(_weight)) {
        throw utility::Illegal_argument_exception("Directed_edge weight argument is NaN");
    }
}

std::string Directed_edge::to_string() const
{
    std::stringstream ss;
    ss << "Directed_edge(" << _source << "->" << _destination << ", weight: " << std::setprecision(2) << _weight << ")";
    return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Directed_edge& out)
{
    return os << out.to_string();
}