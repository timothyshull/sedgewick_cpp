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

    explicit Depth_first_order(Edge_weighted_digraph& g);

    explicit Depth_first_order(Digraph& g);

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

    void _dfs(Edge_weighted_digraph& g, int v);

    void _dfs(Digraph& g, int v);

    bool _check(Digraph& g);
};

#endif //DEPTH_FIRST_ORDER_H
