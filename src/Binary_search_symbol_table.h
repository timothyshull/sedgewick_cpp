#ifndef BINARY_SEARCH_SYMBOL_TABLE_H
#define BINARY_SEARCH_SYMBOL_TABLE_H

#include <vector>
#include <memory>

#include "utility.h"
#include "Queue.h"

template<typename T>
struct Binary_search_symbol_table_comparator {
    int operator()(const T& x, const T& y) const
    {
        if (x < y) {
            return -1;
        } else if (y < x) {
            return 1;
        }
        return 0;
    }
};

template<typename Key, typename Value, typename Comparator = Binary_search_symbol_table_comparator<Key>>
class Binary_search_symbol_table {
public:
    using Key_type = Key;
    using Value_type = Value;
    using Shared_value_type = std::shared_ptr<Value_type>;
    using Raw_value_pointer = Value_type*;
    using Comparator_type = Comparator;

    Binary_search_symbol_table() : Binary_search_symbol_table(init_capacity) {}

    explicit Binary_search_symbol_table(int capacity) : _keys(capacity), _values(capacity) {}

    inline int size() const { return _n; }

    inline bool is_empty() const { return _n == 0; }

    bool contains(Key_type key) const
    {
        return get(key) != nullptr;
    }

    Shared_value_type get(Key_type key) const
    {
        if (is_empty()) {
            return nullptr;
        }
        int i = rank(key);
        if (i < _n && Comparator_type()(_keys[i], key) == 0) {
            return _values[i];
        }
        return nullptr;
    }

    int rank(Key_type key) const
    {
        int lo = 0;
        int hi = _n - 1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            int cmp = Comparator_type()(key, _keys[mid]);
            if (cmp < 0) {
                hi = mid - 1;
            } else if (cmp > 0) {
                lo = mid + 1;
            } else {
                return mid;
            }
        }
        return lo;
    }

    void put(Key_type key, Raw_value_pointer value)
    {
        if (value == nullptr) {
            remove(key);
            return;
        }
        int i = rank(key);

        if (i < _n && Comparator_type()(_keys[i], key) == 0) {
            _values[i] = value;
            return;
        }

        if (_n == _keys.size()) {
            _resize(2 * _keys.size());
        }

        // _keys.insert(_keys.begin() + j, key);
        // _values.insert(_values.begin() + j, value);
        for (auto j = _n; j > i; --j) {
            _keys[j] = _keys[j - 1];
            _values[j] = _values[j - 1];
        }
        _keys[i] = key;
        _values[i] = value;
        ++_n;

        utility::alg_assert(_check(), "Binary_search_symbol_table invariant _check failed after \"put()\"");
    }

    void remove(Key_type key)
    {
        if (is_empty()) { return; }

        int i = rank(key);

        if (i == _n || Comparator_type()(_keys[i], key) != 0) {
            return;
        }

        // _keys.erase(_keys.begin() + i);
        // _values.erase(_values.begin() + i);
        for (auto j = i; j < _n - 1; ++j) {
            _keys[j] = _keys[j + 1];
            _values[j] = _values[j + 1];
        }

        --_n;
        // _keys[_size] = null;
        _values[_n] = nullptr;

        if (_n > 0 && _n == _keys.size() / 4) {
            _resize(_keys.size() / 2);
        }

        utility::alg_assert(_check(), "Binary_search_symbol_table invariant _check failed after \"remove()\"");
    }

    void delete_min()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"Symbol table underflow error"};
        }
        remove(min());
    }

    void delete_max()
    {
        if (is_empty()) {
            throw utility::No_such_element_exception{"Symbol table underflow error"};
        }
        remove(max());
    }

    Key_type min() const
    {
        // TODO: how to handle null keys
        // if (is_empty()) return null;
        return _keys[0];
    }

    Key_type max() const
    {
        // TODO: how to handle null keys
        // if (is_empty()) return null;
        return _keys[_n - 1];
    }

    Key_type select(int k) const
    {
        if (k < 0 || k >= _n) { return nullptr; }
        return _keys[k];
    }

    Key_type floor(Key_type key) const
    {
        if (key == nullptr) {
            throw utility::Illegal_argument_exception{"The key argument to floor() is null"};
        }
        int i = rank(key);
        if (i < _n && Comparator_type()(key, _keys[i]) == 0) {
            return _keys[i];
        }
        if (i == 0) {
            return nullptr;
        } else {
            return _keys[i - 1];
        }
    }

    Key_type ceiling(Key_type key) const
    {
        if (key == nullptr) {
            throw utility::Illegal_argument_exception{"The key argument to ceiling() is null"};
        }
        int i = rank(key);

        if (i == _n) {
            return nullptr;
        } else {
            return _keys[i];
        }
    }

    int size(Key_type lo, Key_type hi) const
    {
        if (lo == nullptr) {
            throw utility::Illegal_argument_exception{"The first argument to size() is null"};
        }
        if (hi == nullptr) {
            throw utility::Illegal_argument_exception{"The second argument to size() is null"};
        }

        if (Comparator_type()(lo, hi) > 0) {
            return 0;
        }
        if (contains(hi)) {
            return rank(hi) - rank(lo) + 1;
        } else {
            return rank(hi) - rank(lo);
        }
    }

    Queue<Key_type> keys(Key_type lo, Key_type hi) const
    {
        if (lo == nullptr) {
            throw utility::Illegal_argument_exception{"The first argument to keys() is null"};
        }
        if (hi == nullptr) {
            throw utility::Illegal_argument_exception{"The second argument to keys() is null"};
        }

        Queue<Key> queue;
        if (Comparator_type(lo, hi) > 0) {
            return queue;
        }
        for (auto i = rank(lo); i < rank(hi); ++i) {
            queue.enqueue(_keys[i]);
        }
        if (contains(hi)) {
            queue.enqueue(_keys[rank(hi)]);
        }
        return queue;
    }

private:
    std::vector<Key_type> _keys;
    std::vector<Shared_value_type> _values;
    int _n;
    int init_capacity = 2;

    void _resize(int capacity)
    {
        utility::alg_assert(capacity >= _n, "The new capacity is not _greater than or equal to the original capacity");
        _keys.resize(capacity);
        _values.resize(capacity);
    }

    bool _check() const
    {
        return _is_sorted() && _rank_check();
    }

    bool _is_sorted() const
    {
        auto comp = Comparator_type{};
        for (auto i = 1; i < _n; ++i) {
            if (comp(_keys[i], _keys[i - 1]) < 0) {
                return false;
            }
        }
        return true;
    }

    bool _rank_check() const
    {
        for (auto i = 0; i < size(); ++i) {
            if (i != rank(select(i))) {
                return false;
            }
        }

        Comparator_type comp;
        for (auto i = 0; i < size(); ++i) {
            if (comp(_keys[i], select(rank(_keys[i]))) != 0) {
                return false;
            }
        }
        return true;
    }
};

#endif // BINARY_SEARCH_SYMBOL_TABLE_H
