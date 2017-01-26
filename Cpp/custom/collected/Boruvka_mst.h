#ifndef BORUVKA_MST_H
#define BORUVKA_MST_H

#include <limits>
#include <vector>
#include "Edge.h"
#include "Edge_weighted_digraph.h"
#include "Bag.h"

class Boruvka_mst {
public:
    Boruvka_mst() = default;

    Boruvka_mst(const Boruvka_mst&) = default;

    Boruvka_mst(Boruvka_mst&&) = default;

    ~Boruvka_mst() = default;

    Boruvka_mst& operator=(const Boruvka_mst&) = default;

    Boruvka_mst& operator=(Boruvka_mst&&) = default;

    Boruvka_mst(Edge_weighted_digraph& digraph);

    inline Bag<Edge> edges() const { return _mst; }

    inline double weight() const noexcept { return _weight; };

    inline static bool less(Edge& e, Edge& f) noexcept { return e.weight() < f.weight(); }

private:
    const static double _epsilon = std::numeric_limits<double>::epsilon();
    Bag<Edge> _mst;
    double _weight;

    bool _check(Edge_weighted_digraph& g);
};

#endif // BORUVKA_MST_H
