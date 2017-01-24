#include "Depth_first_order.h"
#include "Std_out.h"

Depth_first_order::Depth_first_order(Edge_weighted_digraph& g)
        : _pre(static_cast<std::vector<int>::size_type>(g.num_vertices())),
          _post(static_cast<std::vector<int>::size_type>(g.num_vertices())),
          _marked(static_cast<std::deque<bool>::size_type>(g.num_vertices())),
          _pre_counter{0},
          _post_counter{0}
{

    for (int v = 0; v < g.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(g, v);
        }
    }
}

Depth_first_order::Depth_first_order(Digraph& g)
        : _pre(static_cast<std::vector<int>::size_type>(g.num_vertices())),
          _post(static_cast<std::vector<int>::size_type>(g.num_vertices())),
          _marked(static_cast<std::deque<bool>::size_type>(g.num_vertices())),
          _pre_counter{0},
          _post_counter{0}
{

    for (int v = 0; v < g.num_vertices(); ++v) {
        if (!_marked[v]) {
            _dfs(g, v);
        }
    }

    utility::assert(_check(g), "Depth_first_order invariant check for a Digraph failed after construction");
}

void Depth_first_order::_dfs(Edge_weighted_digraph& g, int v)
{
    _marked[v] = true;
    _pre[v] = _pre_counter++;
    _preorder.enqueue(v);
    for (auto w : g.adjacent(v)) {
        if (!_marked[w.to()]) {
            _dfs(g, w.to());
        }
    }
    _postorder.enqueue(v);
    _post[v] = _post_counter++;
}

void Depth_first_order::_dfs(Digraph& g, int v)
{
    _marked[v] = true;
    _pre[v] = _pre_counter++;
    _preorder.enqueue(v);
    for (auto w : g.adjacent(v)) {
        if (!_marked[w]) {
            _dfs(g, w);
        }
    }
    _postorder.enqueue(v);
    _post[v] = _post_counter++;
}

std::vector<int> Depth_first_order::reverse_post() const
{
    std::vector<int> reverse;
    for (auto v : _postorder) {
        reverse.emplace_back(v);
    }
    return reverse;
}

bool Depth_first_order::_check(Digraph& g)
{
    int r = 0;
    for (int v : post()) {
        if (post(v) != r) {
            Std_out::print_line("post(v) and post() are inconsistent");
            return false;
        }
        r++;
    }

    r = 0;
    for (int v : pre()) {
        if (pre(v) != r) {
            Std_out::print_line("pre(v) and pre() are inconsistent");
            return false;
        }
        r++;
    }

    return true;
}
