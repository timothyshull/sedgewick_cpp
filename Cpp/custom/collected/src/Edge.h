#ifndef EDGE_H
#define EDGE_H

#include <string>

class Edge {
public:
    Edge(const Edge&) = default;

    Edge(Edge&&) = default;

    ~Edge() = default;

    Edge& operator=(const Edge&) = default;

    Edge& operator=(Edge&&) = default;

    Edge();

    Edge(int source, int destination, double weight);

    inline double weight() const noexcept { return _weight; }

    inline int either() const noexcept { return _source; }

    int other(int vertex);

    inline bool operator<(const Edge& rhs) const noexcept { return _weight < rhs._weight; }

    inline bool operator==(const Edge& rhs) const noexcept { return _source == rhs._source && _destination == rhs._destination && _weight == rhs._weight; }

    inline bool operator!=(const Edge& rhs) const noexcept { return !(*this == rhs); }

    std::string to_string() { return "Edge(source: " + std::to_string(_source) + ", destination: " + std::to_string(_destination) + ", weight: " + std::to_string(_weight) + ")"; }

private:
    const int _source;
    const int _destination;
    const double _weight;
};

std::ostream& operator<<(std::ostream& os, Edge& out);

#endif // EDGE_H
