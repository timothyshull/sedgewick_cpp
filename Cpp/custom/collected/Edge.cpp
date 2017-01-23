#include "Edge.h"

Edge::Edge(int v, int w, double weight)
{
    if (v < 0) { throw new IndexOutOfBoundsException("Vertex name must be a nonnegative integer"); }
    if (w < 0) { throw new IndexOutOfBoundsException("Vertex name must be a nonnegative integer"); }
    if (Double.isNaN(weight)) { throw new IllegalArgumentException("Weight is NaN"); }
    this.v = v;
    this.w = w;
    this.weight = weight;
}

double Edge::weight()
{
    return weight;
}

int Edge::either()
{
    return v;
}

int Edge::other(int vertex)
{
    if (vertex == v) { return w; }
    else if (vertex == w) { return v; }
    else { throw new IllegalArgumentException("Illegal endpoint"); }
}

bool bool Edge::operator<(Edge& rhs)
{
    return this->weight < rhs.weight;
}

std::string Edge::toString()
{
    return String.format("%d-%d %.5f", v, w, weight);
}

std::ostream& operator<<(std::ostream& os, Edge& out)
{
    return os << out.toString();
}
