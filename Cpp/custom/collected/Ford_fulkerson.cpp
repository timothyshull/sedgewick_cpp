#include "Ford_fulkerson.h"

Ford_fulkerson::Ford_fulkerson(Flow_network& G, int s, int t)
{
    validate(s, G.num_vertices());
    validate(t, G.num_vertices());
    if (s == t) throw utility::Illegal_argument_exception("Source equals sink");
    if (!isFeasible(G, s, t)) throw utility::Illegal_argument_exception("Initial flow is infeasible");

    // while there exists an augmenting path, use it
    value = excess(G, t);
    while (hasAugmentingPath(G, s, t)) {

        // compute bottleneck capacity
        double bottle = Double.POSITIVE_INFINITY;
        for (int v{t}; v != s; v = edgeTo[v].other(v)) {
            bottle = std::min(bottle, edgeTo[v].residual_capacity_to(v));
        }

        // augment flow
        for (int v{t}; v != s; v = edgeTo[v].other(v)) {
            edgeTo[v].add_residual_flow_to(v, bottle);
        }

        value += bottle;
    }

    // _check optimality conditions
    assert check(G, s, t);
}

double Ford_fulkerson::value()
{
    return value;
}

bool Ford_fulkerson::inCut(int v)
{
    validate(v, marked.length);
    return marked[v];
}

void Ford_fulkerson::validate(int v, int V)
{
    if (v < 0 || v >= V)
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (V - 1));
}

bool Ford_fulkerson::hasAugmentingPath(Flow_network& G, int s, int t)
{
    edgeTo = new FlowEdge[G.num_vertices()];
    marked = new boolean[G.num_vertices()];

    // breadth-first search
    Queue<Integer> queue = new Queue<Integer>();
    queue.enqueue(s);
    marked[s] = true;
    while (!queue.is_empty() && !marked[t]) {
        int v = queue.dequeue();

        for (FlowEdge e : G._adjacency_lists(v)) {
            int w = e.other(v);

            // if residual capacity from v to w
            if (e.residualCapacityTo(w) > 0) {
                if (!marked[w]) {
                    edgeTo[w] = e;
                    marked[w] = true;
                    queue.enqueue(w);
                }
            }
        }
    }

    // is there an augmenting path?
    return marked[t];
}

double Ford_fulkerson::excess(Flow_network& G, int v)
{
    double excess = 0.0;
    for (FlowEdge e : G._adjacency_lists(v)) {
        if (v == e.from()) excess -= e.flow();
        else excess += e.flow();
    }
    return excess;
}

bool Ford_fulkerson::isFeasible(Flow_network& G, int s, int t)
{
    for (int v{0}; v < G.num_vertices(); ++v) {
        for (FlowEdge e : G._adjacency_lists(v)) {
            if (e.flow() < -FLOATING_POINT_EPSILON || e.flow() > e.capacity() + FLOATING_POINT_EPSILON) {
                std::cerr << "Edge does not satisfy capacity constraints: " + e;
                return false;
            }
        }
    }

    // _check that net flow into a vertex equals zero, except at source and sink
    if (std::abs(value + excess(G, s)) > FLOATING_POINT_EPSILON) {
        std::cerr << "Excess at source = " + excess(G, s);
        std::cerr << "Max flow         = " + value;
        return false;
    }
    if (std::abs(value - excess(G, t)) > FLOATING_POINT_EPSILON) {
        std::cerr << "Excess at sink   = " + excess(G, t);
        std::cerr << "Max flow         = " + value;
        return false;
    }
    for (int v{0}; v < G.num_vertices(); ++v) {
        if (v == s || v == t) continue;
        else if (std::abs(excess(G, v)) > FLOATING_POINT_EPSILON) {
            std::cerr << "Net flow out of " + v + " doesn't equal zero";
            return false;
        }
    }
    return true;
}

bool Ford_fulkerson::check(Flow_network& G, int s, int t)
{
    if (!isFeasible(G, s, t)) {
        std::cerr << "Flow is infeasible";
        return false;
    }

    // _check that s is on the source side of min cut and that t is not on source side
    if (!inCut(s)) {
        std::cerr << "source " + s + " is not on source side of min cut";
        return false;
    }
    if (inCut(t)) {
        std::cerr << "sink " + t + " is on source side of min cut";
        return false;
    }

    // _check that value of min cut = value of max flow
    double mincutValue = 0.0;
    for (int v{0}; v < G.num_vertices(); ++v) {
        for (FlowEdge e : G._adjacency_lists(v)) {
            if ((v == e.from()) && inCut(e.from()) && !inCut(e.to()))
                mincutValue += e.capacity();
        }
    }

    if (std::abs(mincutValue - value) > FLOATING_POINT_EPSILON) {
        std::cerr << "Max flow value = " + value + ", min cut value = " + mincutValue;
        return false;
    }

    return true;
}
