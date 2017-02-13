// Program 19.7 - Topological sort
#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include <vector>

// Assumes a DAG
template<typename Dag_type>
class Topological_sort {
public:
    Topological_sort(const Dag_type& dag)
            : _dag{dag},
              _t_count(0),
              _count(0),
              _preorder(dag.V(), -1),
              _postorder(dag.V(), -1),
              _postorder_inverse(dag.V(), -1)
    {
        for (int v{0}; v < dag.num_vertices(); ++v) {
            if (_preorder[v] == -1) { _topological_sort_r(v); }
        }
    }

    inline int operator[](int v) const { return _postorder_inverse[v]; }

    inline int relabel(int v) const { return _postorder[v]; }

private:
    const Dag_type& _dag;
    int _count;
    int _t_count;
    std::vector<int> _preorder;
    std::vector<int> _postorder;
    std::vector<int> _postorder_inverse;

    void _topological_sort_r(int v)
    {
        _preorder[v] = _count++;
        for (int w{0}; w < _dag.num_vertices(); ++w) {
            if (_dag.edge(w, v)) {
                if (_preorder[w] == -1) { _topological_sort_r(w); }
            }
        }
        _postorder[v] = _t_count;
        _postorder_inverse[_t_count++] = v;
    }
};



#endif // TOPOLOGICAL_SORT_H
