// Program 20.10 - Multiway heap priority queue implementation
#ifndef MST_PRIM_PFS_H
#define MST_PRIM_PFS_H

#include <vector>

template<typename Key_type>
class Priority_queue_prim_pfs {
public:
    Priority_queue_prim_pfs(int N, const std::vector <Key_type>& a, int d = 3)
            : a(a),
              pq(N + 1, 0),
              qp(N + 1, 0),
              _size(0),
              d(d) {}

    inline int empty() const noexcept { return _size == 0; }

    void insert(int v)
    {
        pq[++_size] = v;
        qp[v] = _size;
        _fix_up(_size);
    }

    int get_min()
    {
        swap(1, _size);
        _fix_down(1, _size - 1);
        return pq[_size--];
    }

    void lower(int k) { _fix_up(qp[k]); }

private:
    int d;
    int _size;
    std::vector<int> pq;
    std::vector<int> qp;
    const std::vector<Key_type>& a;

    void swap(int i, int j)
    {
        int t = pq[i];
        pq[i] = pq[j];
        pq[j] = t;
        qp[pq[i]] = i;
        qp[pq[j]] = j;
    }

    void _fix_up(int k)
    {
        while (k > 1 && a[pq[(k + d - 2) / d]] > a[pq[k]]) {
            swap(k, (k + d - 2) / d);
            k = (k + d - 2) / d;
        }
    }

    void _fix_down(int k, int N)
    {
        int j;
        while ((j = d * (k - 1) + 2) <= N) {
            for (int i = j + 1; i < j + d && i <= N; i++) {
                if (a[pq[j]] > a[pq[i]]) { j = i; }
            }
            if (!(a[pq[k]] > a[pq[j]])) { break; }
            swap(k, j);
            k = j;
        }
    }
};

#endif // MST_PRIM_PFS_H
