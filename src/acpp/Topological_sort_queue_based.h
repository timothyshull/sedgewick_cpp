// Program 19.8 - Source-queue-based topological sort
#ifndef TOPOLOGICAL_SORT_QUEUE_BASED_H
#define TOPOLOGICAL_SORT_QUEUE_BASED_H

#include <queue>

template<typename Dag_type>
class Topological_sort_queue_based {
public:
    Topological_sort_queue_based(const Dag_type& dag)
            : _dag{dag},
              _inorder(dag.num_vertices(), 0),
              _topological_sort(dag.num_vertices(), -1),
              _topological_sort_inverse(dag.num_vertices(), -1)
    {
        std::queue<int> queue;
        for (auto v = 0; v < dag.num_vertices(); ++v) {
            // typename Dag_type::adjIterator A(dag, v);
            for (auto t : dag.adjacent(v)) {
                _inorder[t]++;
            }
        }
        for (auto v = 0; v < dag.num_vertices(); ++v) {
            if (_inorder[v] == 0) { queue.push(v); }
        }
        for (int j = 0; !queue.empty(); ++j) {
            _topological_sort[j] = queue.front();
            queue.pop();
            _topological_sort_inverse[_topological_sort[j]] = j;
            // typename Dag_type::adjIterator A(dag, _topological_sort[j]);
            for (auto t : dag.adjacent(_topological_sort[j])) {
                if (--_inorder[t] == 0) { queue.push(t); }
            }
        }
    }

    int operator[](int v) const { return _topological_sort[v]; }

    int relabel(int v) const { return _topological_sort_inverse[v]; }

private:
    const Dag_type& _dag;
    std::vector<int> _inorder;
    std::vector<int> _topological_sort;
    std::vector<int> _topological_sort_inverse;
};

#endif // TOPOLOGICAL_SORT_QUEUE_BASED_H
