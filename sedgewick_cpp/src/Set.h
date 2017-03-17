#ifndef Set_H
#define Set_H

#include <set>
#include <exception>
#include <iterator>
#include <string>
#include <sstream>

#include "utility.h"

template<typename Key>
class Set {
public:
    using Key_type = Key;
    using Iterator_type = typename std::set<Key_type>::iterator;

    Set() = default;

    Set(const Set&) = default;

    Set(Set&&) = default;

    ~Set() = default;

    Set& operator=(const Set&) = default;

    Set& operator=(Set&&) = default;

    inline Iterator_type begin() { return _set.begin(); }

    inline Iterator_type end() { return _set.end(); }

    inline bool operator==(const Set<Key_type>& rhs) const { return _set == rhs._set; }

    inline void add(Key_type& key) { _set.insert(key); }

    inline void add(Key_type&& key) { _set.insert(key); }

    inline bool contains(Key_type& key) const { return _set.count(key) > 0; }

    inline bool contains(Key_type&& key) const { return _set.count(key) > 0; }

    inline int size() const { return static_cast<int>(_set.size()); }

    inline bool is_empty() const { return _set.empty(); }

    void remove(Key_type& key)
    {
        for (auto it = _set.begin(); it != _set.end(); ++it) {
            if (*it == key) {
                _set.erase(it);
            }
        }
    }

    void remove(Key_type&& key)
    {
        for (auto it = _set.begin(); it != _set.end(); ++it) {
            if (*it == key) {
                _set.erase(it);
            }
        }
    }

    Key_type max()
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called max() with empty set"};
        }
        return *std::max_element(_set.begin(), _set.end());
    }

    Key_type min()
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called min() with empty set"};
        }
        return *std::min_element(_set.begin(), _set.end());
    }

    Key_type ceiling(Key_type& key)
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called ceiling() with empty set"};
        }
        auto result = _set.upper_bound(key);
        if (result == _set.end()) {
            std::stringstream ss;
            ss << "all keys are less than " << key << " or the key is not in the set";
            throw utility::No_such_element_exception{ss.str()};
        }
        if (*(--result) == key) {
            return *result;
        }
        return *(++result);
    }

    Key_type ceiling(Key_type&& key)
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called ceiling() with empty set"};
        }
        auto result = _set.upper_bound(key);
        if (result == _set.end()) {
            std::stringstream ss;
            ss << "all keys are less than " << key << " or the key is not in the set";
            throw utility::No_such_element_exception{ss.str()};
        }
        if (*(--result) == key) {
            return *result;
        }
        return *(++result);
    }

    Key_type floor(Key_type& key)
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called floor() with empty set"};
        }
        auto result = _set.lower_bound(key);
        if (*result == key) {
            return *result;
        } else if (result != _set.begin()) {
            return *(--result);
        } else {
            std::stringstream ss;
            ss << "all keys are greater than " << key;
            throw utility::No_such_element_exception{ss.str()};
        }
    }

    Key_type floor(Key_type&& key)
    {
        if (_set.empty()) {
            throw utility::No_such_element_exception{"called floor() with empty set"};
        }
        auto result = _set.lower_bound(key);
        if (*result == key) {
            return *result;
        } else if (result != _set.begin()) {
            return *(--result);
        } else {
            std::stringstream ss;
            ss << "all keys are greater than " << key;
            throw utility::No_such_element_exception{ss.str()};
        }
    }

//    Key_type floor(Key_type&& key)
//    {
//        if (_set.empty()) {
//            throw utility::No_such_element_exception{"called floor() with empty set"};
//        }
//        auto result = _set.find(key);
//        if (result == _set.end()) {
//            std::stringstream ss;
//            ss << key << " is not in the set";
//            throw utility::No_such_element_exception{ss.str()};
//        } else if (result == _set.begin()) {
//            std::stringstream ss;
//            ss << "all keys are greater than " << key;
//            throw utility::No_such_element_exception{ss.str()};
//        }
//        return *(--result);
//    }

    Set<Key_type> create_union(Set<Key_type>& rhs)
    {
        std::set<Key_type> dest;
        std::set_union(_set.begin(), _set.end(), rhs.begin(), rhs.end(), std::back_inserter(dest));
        return {dest};
    }

    Set<Key_type> intersection(Set<Key_type>& rhs)
    {
        std::set<Key_type> dest;
        std::set_intersection(_set.begin(), _set.end(), rhs.begin(), rhs.end(), std::back_inserter(dest));
        return {dest};
    }

    std::string to_string()
    {
        std::stringstream ss;
        ss << "Set(\n";
        for (auto key : _set) {
            ss << "    " << key << ",\n";
        }
        ss << ")";
        return ss.str();
    }

private:
    std::set<Key_type> _set;

    Set(std::set<Key_type>& x) : _set{x} {}
};

#endif // Set_H
