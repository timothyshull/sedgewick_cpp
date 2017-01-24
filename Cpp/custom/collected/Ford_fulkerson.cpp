#include "Ford_fulkerson.h"

Ford_fulkerson::Ford_fulkerson(Flow_network& G, int s, int t)
{
    validate(s, G.num_vertices());
    validate(t, G.num_vertices());
    if (s == t) throw new IllegalArgumentException("Source equals sink");
    if (!isFeasible(G, s, t)) throw new IllegalArgumentException("Initial flow is infeasible");

    // while there exists an augmenting path, use it
    value = excess(G, t);
    while (hasAugmentingPath(G, s, t)) {

        // compute bottleneck capacity
        double bottle = Double.POSITIVE_INFINITY;
        for (int v = t; v != s; v = edgeTo[v].other(v)) {
            bottle = Math.min(bottle, edgeTo[v].residualCapacityTo(v));
        }

        // augment flow
        for (int v = t; v != s; v = edgeTo[v].other(v)) {
            edgeTo[v].addResidualFlowTo(v, bottle);
        }

        value += bottle;
    }

    // check optimality conditions
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

        for (FlowEdge e : G.adj(v)) {
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
    for (FlowEdge e : G.adj(v)) {
        if (v == e.from()) excess -= e.flow();
        else excess += e.flow();
    }
    return excess;
}

bool Ford_fulkerson::isFeasible(Flow_network& G, int s, int t)
{
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (FlowEdge e : G.adj(v)) {
            if (e.flow() < -FLOATING_POINT_EPSILON || e.flow() > e.capacity() + FLOATING_POINT_EPSILON) {
                System.err.print_line("Edge does not satisfy capacity constraints: " + e);
                return false;
            }
        }
    }

    // check that net flow into a vertex equals zero, except at source and sink
    if (Math.abs(value + excess(G, s)) > FLOATING_POINT_EPSILON) {
        System.err.print_line("Excess at source = " + excess(G, s));
        System.err.print_line("Max flow         = " + value);
        return false;
    }
    if (Math.abs(value - excess(G, t)) > FLOATING_POINT_EPSILON) {
        System.err.print_line("Excess at sink   = " + excess(G, t));
        System.err.print_line("Max flow         = " + value);
        return false;
    }
    for (int v = 0; v < G.num_vertices(); ++v) {
        if (v == s || v == t) continue;
        else if (Math.abs(excess(G, v)) > FLOATING_POINT_EPSILON) {
            System.err.print_line("Net flow out of " + v + " doesn't equal zero");
            return false;
        }
    }
    return true;
}

bool Ford_fulkerson::check(Flow_network& G, int s, int t)
{
    if (!isFeasible(G, s, t)) {
        System.err.print_line("Flow is infeasible");
        return false;
    }

    // check that s is on the source side of min cut and that t is not on source side
    if (!inCut(s)) {
        System.err.print_line("source " + s + " is not on source side of min cut");
        return false;
    }
    if (inCut(t)) {
        System.err.print_line("sink " + t + " is on source side of min cut");
        return false;
    }

    // check that value of min cut = value of max flow
    double mincutValue = 0.0;
    for (int v = 0; v < G.num_vertices(); ++v) {
        for (FlowEdge e : G.adj(v)) {
            if ((v == e.from()) && inCut(e.from()) && !inCut(e.to()))
                mincutValue += e.capacity();
        }
    }

    if (Math.abs(mincutValue - value) > FLOATING_POINT_EPSILON) {
        System.err.print_line("Max flow value = " + value + ", min cut value = " + mincutValue);
        return false;
    }

    return true;
}
