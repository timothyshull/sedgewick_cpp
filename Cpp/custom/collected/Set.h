#ifndef SET_H
#define SET_H

#include <set>
#include <exception>
#include <iterator>

template<typename Key_type>
class Set {
private:
    std::set<Key_type> set_;

public:
    Set() : set_{std::set<Key_type>{}} {}

    Set(std::set<Key_type>& x) : set_{x} {}

    void add(Key_type key)
    {
        set_.insert(key);
    }

    void add(Key_type& key)
    {
        set_.insert(key);
    }

    bool contains(Key_type& key)
    {
        auto search = set_.find(key);
        return search != set_.end();
    }

    bool contains(Key_type key)
    {
        auto search = set_.find(key);
        return search != set_.end();
    }

    inline typename std::set<Key_type>::size_type size() { return set_.size(); }

    bool is_empty() { return set_.empty(); }

    Key_type& max()
    {
        if (set_.empty()) {
            throw std::exception{};
        }
        return *std::max_element(set_.begin(), set_.end());
    }

    Key_type& min()
    {
        if (set_.empty()) {
            throw std::exception{};
        }
        return *std::min_element(set_.begin(), set_.end());
    }

    Key_type& ceiling(Key_type& key)
    {
        if (set_.empty()) {
            throw std::exception{};
        }
        auto result = set_.find(key);
        auto next = result;
        auto end = set_.end();
        std::advance(next, 1);
        if (result == end || next == end) {
            throw std::exception{};
        }
        return *next;
    }
};

#endif // SET_H
