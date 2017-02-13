#ifndef REVERSE_TOPOLOGICAL_SORT_H
#define REVERSE_TOPOLOGICAL_SORT_H

#include <vector>

template<typename Dag_type>
class Reverse_topological_sort {
public:
    Reverse_topological_sort(const Dag_type& dag)
            : _dag{dag},
              _t_count{0},
              _count{0},
              _preorder(dag.num_vertices(), -1),
              _postorder(dag.num_vertices(), -1),
              _postorder_inverse(dag.num_vertices(), -1)
    {
        for (int v{0}; v < dag.num_vertices(); ++v) { if (_preorder[v] == -1) { _topological_sort_r(v); }}
    }

    inline int operator[](int v) const { return _postorder_inverse[v]; }

    inline int relabel(int v) const { return _postorder[v]; }

private:
    const Dag_type& _dag;
    int _count;
    int _t_count;
    std::vector<int> _preorder;
    std::vector<int>_postorder;
    std::vector<int>_postorder_inverse;

    void _topological_sort_r(int v)
    {
        _preorder[v] = _count++;
        // typename Dag_type::adjIterator A(_dag, v);
        for (auto t : _dag.adjacent(v)) {
            if (_preorder[t] == -1) { _topological_sort_r(t); }
        }
        _postorder[v] = _t_count;
        _postorder_inverse[_t_count++] = v;
    }
};



#endif // REVERSE_TOPOLOGICAL_SORT_H
