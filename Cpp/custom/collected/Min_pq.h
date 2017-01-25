#ifndef MIN_PQ_H
#define MIN_PQ_H

#include <vector>
#include "utility.h"

template<typename T, typename Comparator = std::less<T>>
class Min_pq {
public:
    using Iterator_type = typename std::vector<T>::iterator;

    Min_pq(int capacity) : _size{0}, _priority_queue{}
    {
        _priority_queue.reserve(capacity + 1);
    }

    Min_pq() : Min_pq(1) {}

    Min_pq(std::vector<T>& keys) : _size{keys.size()}, _priority_queue{}
    {
        _priority_queue.reserve(keys.size() + 1);
        for (int i{0}; i < _size; ++i) {
            _priority_queue[i + 1] = keys[i];
        }
        for (int k{_size / 2}; k >= 1; --k) {
            _sink(k);
        }
        utility::assert(_is_min_heap(), "Min_pq is_min_heap _check failed");
    }

    inline bool is_empty() const { return _size == 0; }

    inline int size() const { return _size; }

    T& min()
    {
        if (is_empty()) { throw utility::No_such_element_exception("Priority _queue underflow"); }
        return _priority_queue[1];
    }

    void insert(T& x)
    {
        if (_size == _priority_queue.size() - 1) { _resize(2 * _priority_queue.size()); }

        _priority_queue[++_size] = x;
        _swim(_size);
        utility::assert(_is_min_heap(), "Min_pq _is_min_heap _check failed");
    }

    T delete_min()
    {
        if (is_empty()) { throw utility::No_such_element_exception("Priority _queue underflow"); }
        _exch(1, _size);
        T min = _priority_queue[_size--];
        _sink(1);
        std::remove(_priority_queue.begin() + _size + 1);
        // _priority_queue[_size + 1] = null;         // avoid loitering and help with garbage collection
        if ((_size > 0) && (_size == (_priority_queue.size() - 1) / 4)) { _resize(_priority_queue.size() / 2); }
        utility::assert(_is_min_heap(), "Min_pq _is_min_heap _check failed");
        return min;
    }

    Iterator_type begin() { return _priority_queue.begin(); }

    Iterator_type end() { return _priority_queue.end(); }

private:
    std::vector<T> _priority_queue;
    int _size;
    Comparator _comparator;

    void _resize(int capacity)
    {
        utility::assert(capacity > _size, "Min_pq capacity _check failed");
        std::vector<T> temp{};
        temp.reserve(capacity);
        for (int i{1}; i <= _size; ++i) {
            temp[i] = _priority_queue[i];
        }
        _priority_queue = temp;
    }

    void _swim(int k)
    {
        while (k > 1 && _greater(k / 2, k)) {
            _exch(k, k / 2);
            k = k / 2;
        }
    }

    void _sink(int k)
    {
        while (2 * k <= _size) {
            int j = 2 * k;
            if (j < _size && _greater(j, j + 1)) { ++j; }
            if (!_greater(k, j)) {
                break;
            }
            _exch(k, j);
            k = j;
        }
    }

    bool _greater(int i, int j) const
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

    bool _is_min_heap() const
    {
        return _is_min_heap(1);
    }

    bool _is_min_heap(int k) const
    {
        if (k > _size) {
            return true;
        }
        int left = 2 * k;
        int right = 2 * k + 1;
        if (left <= _size && _greater(k, left)) {
            return false;
        }
        if (right <= _size && _greater(k, right)) {
            return false;
        }
        return _is_min_heap(left) && _is_min_heap(right);
    }
};

#endif // MIN_PQ_H
