#include "Ford_fulkerson.h"
#include "Queue.h"
#include "utility.h"

Ford_fulkerson::Ford_fulkerson(Flow_network& network, int source, int dest)
{
    _validate(source, network.num_vertices());
    _validate(dest, network.num_vertices());
    if (source == dest) {
        throw utility::Illegal_argument_exception{"Source equals sink"};
    }
    if (!_is_feasible(network, source, dest)) {
        throw utility::Illegal_argument_exception{"Initial flow is infeasible"};
    }

    _value = _excess(network, dest);
    double bottle;
    while (_has_augmenting_path(network, source, dest)) {
        bottle = std::numeric_limits<double>::infinity();
        for (int v{dest}; v != source; v = _edge_to[v].other(v)) {
            bottle = std::min(bottle, _edge_to[v].residual_capacity_to(v));
        }

        for (int v{dest}; v != source; v = _edge_to[v].other(v)) {
            _edge_to[v].add_residual_flow_to(v, bottle);
        }

        _value += bottle;
    }

    utility::alg_assert(_check(network, source, dest), "Ford_fulkerson invariant check failed after construction");
}

bool Ford_fulkerson::in_cut(int vertex)
{
    _validate(vertex, static_cast<int>(_marked.size()));
    return _marked[vertex];
}

void Ford_fulkerson::_validate(int vertex, int num_vertices)
{
    if (vertex < 0 || vertex >= num_vertices) {
        std::string s{"vertex " + std::to_string(vertex) + " is not between 0 and " + std::to_string(num_vertices - 1)};
        throw utility::Index_out_of_bounds_exception{s};
    }
}

bool Ford_fulkerson::_has_augmenting_path(Flow_network& network, int source, int dest)
{
    _edge_to = std::vector<Flow_edge>{};
    _edge_to.reserve(static_cast<std::vector<Flow_edge>::size_type>(network.num_vertices()));
    _marked = std::deque<bool>(static_cast<std::deque<bool>::size_type>(network.num_vertices()));

    Queue<int> queue;
    queue.enqueue(source);
    _marked[source] = true;
    int v;
    int w;
    while (!queue.is_empty() && !_marked[dest]) {
        v = queue.dequeue();

        for (auto e : network.adjacent(v)) {
            w = e.other(v);

            if (e.residual_capacity_to(w) > 0) {
                if (!_marked[w]) {
                    _edge_to[w] = e;
                    _marked[w] = true;
                    queue.enqueue(w);
                }
            }
        }
    }

    return _marked[dest];
}

double Ford_fulkerson::_excess(Flow_network& network, int vertex)
{
    double excess{0.0};
    for (auto e : network.adjacent(vertex)) {
        if (vertex == e.from()) { excess -= e.flow(); }
        else { excess += e.flow(); }
    }
    return excess;
}

bool Ford_fulkerson::_is_feasible(Flow_network& network, int source, int dest)
{
    for (int v{0}; v < network.num_vertices(); ++v) {
        for (auto e : network.adjacent(v)) {
            if (e.flow() < -floating_point_epsilon || e.flow() > e.capacity() + floating_point_epsilon) {
                std::cerr << "Edge does not satisfy capacity constraints: " << e;
                return false;
            }
        }
    }

    if (std::abs(_value + _excess(network, source)) > floating_point_epsilon) {
        std::cerr << "Excess at source = " << _excess(network, source);
        std::cerr << "Max flow         = " << _value;
        return false;
    }
    if (std::abs(_value - _excess(network, dest)) > floating_point_epsilon) {
        std::cerr << "Excess at sink   = " << _excess(network, dest);
        std::cerr << "Max flow         = " << _value;
        return false;
    }
    for (int v{0}; v < network.num_vertices(); ++v) {
        if (v == source || v == dest) { continue; }
        else if (std::abs(_excess(network, v)) > floating_point_epsilon) {
            std::cerr << "Net flow out of " << v << " doesn't equal zero";
            return false;
        }
    }
    return true;
}

bool Ford_fulkerson::_check(Flow_network& G, int s, int t)
{
    if (!_is_feasible(G, s, t)) {
        std::cerr << "Flow is infeasible";
        return false;
    }

    if (!in_cut(s)) {
        std::cerr << "source " << s << " is not on source side of min cut";
        return false;
    }
    if (in_cut(t)) {
        std::cerr << "sink " << t << " is on source side of min cut";
        return false;
    }

    double mincut_value{0.0};
    for (int v{0}; v < G.num_vertices(); ++v) {
        for (auto e : G.adjacent(v)) {
            if ((v == e.from()) && in_cut(e.from()) && !in_cut(e.to())) {
                mincut_value += e.capacity();
            }
        }
    }

    if (std::abs(mincut_value - _value) > floating_point_epsilon) {
        std::cerr << "Max flow value = " << _value << ", min cut value = " << mincut_value;
        return false;
    }

    return true;
}
