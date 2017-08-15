#include "Suffix_array.h"
#include "utility.h"

Suffix::Suffix(std::string& text, int index) : _text{text}, _index{index} {}

bool Suffix::operator<(const Suffix& rhs) const
{
    if (*this == rhs) { return false; }
    auto n = std::min(_length(), rhs._size());
    for (auto i = 0; i < n; ++i) {
        if ((*this)[i] < rhs[i]) { return true; }
        if ((*this)[i] > rhs[i]) { return false; }
    }
    return _length() - rhs._size() < 0;
}

Suffix_array::Suffix_array(std::string& text)
        : _suffixes(text.size())
{
    auto n = text.size();
    for (auto i = 0; i < n; ++i) {
        _suffixes[i] = Suffix(text, i);
    }
    std::sort(_suffixes.begin(), _suffixes.end());
}

int Suffix_array::index(int i)
{
    if (i < 0 || i >= _suffixes.size()) { throw utility::Index_out_of_bounds_exception{""}; }
    return _suffixes[i]._index;
}

int Suffix_array::lcp(int i)
{
    if (i < 1 || i >= _suffixes.size()) { throw utility::Index_out_of_bounds_exception{""}; }
    return _lcp(_suffixes[i], _suffixes[i - 1]);
}

std::string Suffix_array::select(int i)
{
    if (i < 0 || i >= _suffixes.size()) { throw utility::Index_out_of_bounds_exception{""}; }
    return _suffixes[i].to_string();
}

int Suffix_array::rank(std::string& query)
{
    int lo = 0;
    int hi = static_cast<int>(_suffixes.size() - 1);
    while (lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        if (query < _suffixes[mid]) {
            hi = mid - 1;
        } else if (_suffixes[mid] < query) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return lo;
}

int Suffix_array::rank(std::string&& query)
{
    int lo = 0;
    int hi = static_cast<int>(_suffixes.size() - 1);
    while (lo <= hi) {
        auto mid = lo + (hi - lo) / 2;
        if (query < _suffixes[mid]) {
            hi = mid - 1;
        } else if (_suffixes[mid] < query) {
            lo = mid + 1;
        } else {
            return mid;
        }
    }
    return lo;
}

int Suffix_array::_lcp(Suffix& s, Suffix& t)
{
    auto n = std::min(s._size(), t._size());
    for (auto i = 0; i < n; ++i) {
        if (s[i] != t[i]) { return i; }
    }
    return static_cast<int>(n);
}

bool bool Suffix_array::operator<(std::string& query, Suffix& suffix)
{
    auto n = std::min(query.size(), suffix._size());
    for (auto i = 0; i < n; ++i) {
        if (query[i] < suffix[i]) { return true; }
        if (query[i] > suffix[i]) { return false; }
    }
    return query.size() - suffix._size() < 0;
}
