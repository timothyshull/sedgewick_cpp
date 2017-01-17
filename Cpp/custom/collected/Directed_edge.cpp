#include <sstream>
#include <iomanip>
#include "Directed_edge.h"

Directed_edge::Directed_edge(unsigned source, unsigned destination, double weight) : _source{source}, _destination{destination}, _weight{weight}
{
    // removed check for value by making input unsigned
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