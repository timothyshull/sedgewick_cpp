#ifndef DEPTH_FIRST_ORDER_H
#define DEPTH_FIRST_ORDER_H

#include <deque>
#include <vector>
#include "Queue.h"
#include "Digraph.h"
#include "Edge_weighted_digraph.h"

class Depth_first_order {
public:
    Depth_first_order() = default;

    Depth_first_order(const Depth_first_order&) = default;

    Depth_first_order(Depth_first_order&&) = default;

    ~Depth_first_order() = default;

    Depth_first_order& operator=(const Depth_first_order&) = default;

    Depth_first_order& operator=(Depth_first_order&&) = default;

    template<typename Graph_type,
            typename = std::enable_if<std::is_same<Graph_type, Digraph>::value
                                      || std::is_same<Graph_type, Edge_weighted_digraph>::value>>
    explicit Depth_first_order(Graph_type& g)
            : _pre{static_cast<std::vector<int>::size_type>(g.num_vertices())},
              _post{static_cast<std::vector<int>::size_type>(g.num_vertices())},
              _marked{static_cast<std::deque<bool>::size_type>(g.num_vertices())},
              _pre_counter{0},
              _post_counter{0}
    {

        for (int v = 0; v < g.num_vertices(); v++) {
            if (!_marked[v]) {
                _dfs(g, v);
            }
        }

        if (std::is_same<Graph_type, Digraph>::value) {
            utility::assert(_check(g), "Depth_first_order invariant check for a Digraph failed after construction");
        }
    }

    inline int pre(int v) const { return _pre[v]; }

    inline int post(int v) const { return _post[v]; }

    inline Queue<int> pre() const { return _preorder; }

    inline Queue<int> post() const { return _postorder; }

    std::vector<int> reverse_post() const;

private:
    std::deque<bool> _marked;
    std::vector<int> _pre;
    std::vector<int> _post;
    Queue<int> _preorder;
    Queue<int> _postorder;
    int _pre_counter;
    int _post_counter;

    template<typename Digraph_type>
    void _dfs(Digraph_type& g, int v);

    bool _check(Digraph& g);
};

template<typename Digraph_type>
void Depth_first_order::_dfs(Digraph_type& g, int v)
{
    _marked[v] = true;
    _pre[v] = _pre_counter++;
    _preorder.enqueue(v);
    for (int w : g.adjacent(v)) {
        if (!_marked[w]) {
            _dfs(g, w);
        }
    }
    _postorder.enqueue(v);
    _post[v] = _post_counter++;
}

#endif //DEPTH_FIRST_ORDER_H
