#include "Topological.h"
#include "Directed_cycle.h"
#include "Depth_first_order.h"
#include "Edge_weighted_directed_cycle.h"

Topological::Topological(Digraph& g)
{
    Directed_cycle finder{g};
    if (!finder.has_cycle()) {
        Depth_first_order dfs{g};
        _order = dfs.reverse_post();
        _rank = std::vector<int>(static_cast<std::vector<int>::size_type>(g.num_vertices()));
        int i = 0;
        for (int v : _order) {
            _rank[v] = ++i;
        }
    }
}

Topological::Topological(Edge_weighted_digraph& g)
{
    Edge_weighted_directed_cycle finder{g};
    if (!finder.has_cycle()) {
        Depth_first_order dfs{g};
        _order = dfs.reverse_post();
    }
}

int Topological::rank(int v) const
{
    _validate_vertex(v);
    if (has_order()) {
        return _rank[v];
    }
    return -1;
}

void Topological::_validate_vertex(int v) const
{
    auto sz = _rank.size();
    if (v < 0 || v >= sz) {
        std::stringstream ss;
        ss << "Vertex " << v << " is not between 0 and " << sz - 1;
        throw utility::Index_out_of_bounds_exception(ss.str());
    }
}
