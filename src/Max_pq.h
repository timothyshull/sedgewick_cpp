#ifndef MAX_PQ_H
#define MAX_PQ_H

#include <vector>
#include "utility.h"

template<typename T, typename Comparator = std::less<T>>
class Max_pq {
public:
    using Iterator_type = typename std::vector<T>::iterator;

    Max_pq(int capacity) : _size{0}, _priority_queue{}
    {
        _priority_queue.reserve(capacity + 1);
        _size = 0;
    }

    Max_pq() : Max_pq{1} {}

    Max_pq(std::vector<T>& keys) : _size{keys.size()}, _priority_queue{}
    {
        _priority_queue.reserve(keys.size() + 1);
        for (auto i = 0; i < _size; ++i) {
            _priority_queue[i + 1] = keys[i];
        }
        for (auto k = _size / 2; k >= 1; --k) {
            _sink(k);
        }
        utility::alg_assert(_is_max_heap(), "Max_pq _is_max_heap _check failed");
    }

    bool is_empty()
    {
        return _size == 0;
    }

    int size()
    {
        return _size;
    }

    T& max()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue underflow"}; }
        return _priority_queue[1];
    }

    void insert(T& x)
    {
        if (_size >= _priority_queue.size() - 1) { resize(2 * _priority_queue.size()); }

        _priority_queue[++_size] = x;
        _swim(_size);
        utility::alg_assert(_is_max_heap(), "Max_pq _is_max_heap _check failed");
    }

    T delete_max()
    {
        if (is_empty()) { throw utility::No_such_element_exception{"Priority _queue underflow"}; }
        T max = _priority_queue[1];
        _exch(1, _size--);
        _sink(1);
        std::remove(_priority_queue.begin() + _size + 1);
        if ((_size > 0) && (_size == (_priority_queue.size() - 1) / 4)) { resize(_priority_queue.size() / 2); }
        utility::alg_assert(_is_max_heap(), "Max_pq _is_max_heap _check failed");
        return max;
    }

    Iterator_type begin() { return _priority_queue.begin(); }

    Iterator_type end() { return _priority_queue.end(); }

private:
    std::vector<T> _priority_queue;
    int _size;
    Comparator _comparator;

    void resize(int capacity)
    {
        utility::alg_assert(capacity > _size, "Max_pq capacity _check failed");
        std::vector<T> temp{};
        temp.reserve(capacity);
        for (auto i = 1; i <= _size; ++i) {
            temp[i] = _priority_queue[i];
        }
        _priority_queue = temp;
    }

    void _swim(int k)
    {
        while (k > 1 && _less(k / 2, k)) {
            _exch(k, k / 2);
            k = k / 2;
        }
    }

    void _sink(int k)
    {
        while (2 * k <= _size) {
            int j = 2 * k;
            if (j < _size && _less(j, j + 1)) { ++j; }
            if (!_less(k, j)) { break; }
            _exch(k, j);
            k = j;
        }
    }

    bool _less(int i, int j)
    {
        if (std::is_same<Comparator, void>::value) {
            return _priority_queue[i] < _priority_queue[j];
        } else {
            return _comparator(_priority_queue[i], _priority_queue[j]);
        }
    }

    void _exch(int i, int j)
    {
        T swap = _priority_queue[i];
        _priority_queue[i] = _priority_queue[j];
        _priority_queue[j] = swap;
    }

    bool _is_max_heap()
    {
        return _is_max_heap(1);
    }

    bool _is_max_heap(int k)
    {
        if (k > _size) { return true; }
        int left = 2 * k;
        int right = 2 * k + 1;
        if (left <= _size && _less(k, left)) { return false; }
        if (right <= _size && _less(k, right)) { return false; }
        return _is_max_heap(left) && _is_max_heap(right);
    }
};

#endif // MAX_PQ_H
