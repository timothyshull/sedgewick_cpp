#include "Hopcroft_karp.h"

Hopcroft_karp::Hopcroft_karp(Graph& G)
{
    _bipartition = new BipartiteX(G);
    if (!_bipartition.is_bipartite()) {
        throw utility::Illegal_argument_exception("graph is not bipartite");
    }

    // initialize empty matching
    this.V = G.num_vertices();
    _mate = new int[_num_vertices];
    for (int v{0}; v < _num_vertices; ++v) {
        _mate[v] = _unmatched;
    }

    // the call to _has_augmenting_path() provides enough info to reconstruct level graph
    while (_has_augmenting_path(G)) {

        // to be able to iterate over each adjacency list, keeping track of which
        // vertex _in each adjacency list needs to be explored next
        Iterator<Integer>[]
        adj = (Iterator<Integer>[])
        new Iterator[G.num_vertices()];
        for (int v{0}; v < G.num_vertices(); ++v) {
            adj[v] = G.adj(v).iterator();
        }

        // for each unmatched vertex s on one side of _bipartition
        for (int s{0}; s < _num_vertices; ++s) {
            if (is_matched(s) || !_bipartition.color(s)) { continue; }   // or use _distance_to[s] == 0

            // find augmenting path from s using nonrecursive DFS
            Stack <Integer> path = new Stack<Integer>();
            path.push(s);
            while (!path.is_empty()) {
                int v = path.peek();

                // retreat, no more edges _in level graph leaving v
                if (!adj[v].hasNext())
                    path.pop();

                    // advance
                else {
                    // process edge v-w only if it is an edge _in level graph
                    int w = adj[v].next();
                    if (!_is_level_graph_edge(v, w)) continue;

                    // add w to augmenting path
                    path.push(w);

                    // augmenting path found: update the matching
                    if (!is_matched(w)) {
                        // Std_out::print_line("augmenting path: " + to_string(path));

                        while (!path.is_empty()) {
                            int x = path.pop();
                            int y = path.pop();
                            _mate[x] = y;
                            _mate[y] = x;
                        }
                        ++cardinality;
                    }
                }
            }
        }
    }

    // also find a min vertex cover
    in_min_vertex_cover = new boolean[_num_vertices];
    for (int v{0}; v < _num_vertices; ++v) {
        if (_bipartition.color(v) && !_marked[v]) { in_min_vertex_cover[v] = true; }
        if (!_bipartition.color(v) && _marked[v]) { in_min_vertex_cover[v] = true; }
    }

    assert certifySolution(G);
}

int Hopcroft_karp::mate(int v)
{
    validate(v);
    return _mate[v];
}

bool Hopcroft_karp::is_matched(int v)
{
    validate(v);
    return _mate[v] != _unmatched;
}

int Hopcroft_karp::size()
{
    return cardinality;
}

bool Hopcroft_karp::is_perfect()
{
    return cardinality * 2 == _num_vertices;
}

bool Hopcroft_karp::in_min_vertex_cover(int v)
{
    validate(v);
    return in_min_vertex_cover[v];
}

std::string Hopcroft_karp::to_string(std::vector<int>& path)
{
    std::stringstream sb = new std::stringstream();
    for (int v : path) {
        sb.append(v + "-");
    }
    std::string s = sb.to_string();
    s = s.substring(0, s.lastIndexOf('-'));
    return s;
}

bool Hopcroft_karp::_is_level_graph_edge(int v, int w)
{
    return (_distance_to[w] == _distance_to[v] + 1) && _is_residual_graph_edge(v, w);
}

bool Hopcroft_karp::_is_residual_graph_edge(int v, int w)
{
    if ((_mate[v] != w) && _bipartition.color(v)) { return true; }
    if ((_mate[v] == w) && !_bipartition.color(v)) { return true; }
    return false;
}

bool Hopcroft_karp::_has_augmenting_path(Graph& G)
{
    _marked = new boolean[_num_vertices];
    _distance_to = new int[_num_vertices];
    for (int v{0}; v < _num_vertices; ++v) {
        _distance_to[v] = Integer.MAX_VALUE;
    }

    // breadth-first search (starting from all unmatched vertices on one side of _bipartition)
    Queue <Integer> queue = new Queue<Integer>();
    for (int v{0}; v < _num_vertices; ++v) {
        if (_bipartition.color(v) && !is_matched(v)) {
            queue.enqueue(v);
            _marked[v] = true;
            _distance_to[v] = 0;
        }
    }

    // run BFS until an augmenting path is found
    // (and keep going until all vertices at that distance are explored)
    bool hasAugmentingPath = false;
    while (!queue.is_empty()) {
        int v = queue.dequeue();
        for (int w : G.adj(v)) {

            // forward edge not _in matching or backwards edge _in matching
            if (_is_residual_graph_edge(v, w)) {
                if (!_marked[w]) {
                    _distance_to[w] = _distance_to[v] + 1;
                    _marked[w] = true;
                    if (!is_matched(w)) {
                        hasAugmentingPath = true;
                    }

                    // stop enqueuing vertices once an alternating path has been discovered
                    // (no vertex on same side will be _marked if its shortest path distance longer)
                    if (!hasAugmentingPath) { queue.enqueue(w); }
                }
            }
        }
    }

    return hasAugmentingPath;
}

void Hopcroft_karp::validate(int v)
{
    if (v < 0 || v >= _num_vertices) {
        throw new IndexOutOfBoundsException("vertex " + v + " is not between 0 and " + (_num_vertices - 1));
    }
}

bool Hopcroft_karp::_certify_solution(Graph& G)
{
    for (int v{0}; v < _num_vertices; ++v) {
        if (_mate(v) == -1) { continue; }
        if (_mate(_mate(v)) != v) { return false; }
    }

    // _check that size() is consistent with _mate()
    int matchedVertices = 0;
    for (int v{0}; v < _num_vertices; ++v) {
        if (_mate(v) != -1) { ++matchedVertices; }
    }
    if (2 * size() != matchedVertices) { return false; }

    // _check that size() is consistent with minVertexCover()
    int sizeOfMinVertexCover = 0;
    for (int v{0}; v < _num_vertices; ++v) {
        if (in_min_vertex_cover(v)) { ++sizeOfMinVertexCover; }
    }
    if (size() != sizeOfMinVertexCover) { return false; }

    // _check that _mate() uses each vertex at most once
    std::deque<bool>
    isMatched = new boolean[_num_vertices];
    for (int v{0}; v < _num_vertices; ++v) {
        int w = _mate[v];
        if (w == -1) { continue; }
        if (v == w) { return false; }
        if (v >= w) { continue; }
        if (isMatched[v] || isMatched[w]) { return false; }
        isMatched[v] = true;
        isMatched[w] = true;
    }

    // _check that _mate() uses only edges that appear _in the graph
    for (int v{0}; v < _num_vertices; ++v) {
        if (_mate(v) == -1) { continue; }
        bool isEdge = false;
        for (int w : G.adj(v)) {
            if (_mate(v) == w) { isEdge = true; }
        }
        if (!isEdge) { return false; }
    }

    // _check that in_min_vertex_cover() is a vertex cover
    for (int v{0}; v < _num_vertices; ++v) {
        for (int w : G.adj(v)) {
            if (!in_min_vertex_cover(v) && !in_min_vertex_cover(w)) { return false; }
        }
    }

    return true;
}
