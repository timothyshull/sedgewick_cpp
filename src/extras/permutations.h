#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>

// from Sedgewick's perms talk -> see wiki heaps algorithm

// Compute all perms of a global array by exchanging each
// element to the end, then recursively permuting the others
template<typename Item_t, typename Visitor_type>
void perms_backtracking(std::vector<Item_t>& v, int n, Visitor_type& visit)
{
    int c;
    if (n == 1) { visit(v); }
    for (c = 1; c <= n; ++c) {
        std::swap(c, n);
        perms_backtracking(v, n - 1, visit);
        std::swap(c, n);
    }
}

// assumes index table v
template<typename Item_t, typename Visitor_type>
void perms_single_exch_r(std::vector<Item_t>& v, int n, Visitor_type& visit)
{
    int c;
    if (n == 1) { visit(v); }
    for (c = 1; c <= n; ++c) {
        perms_single_exch_r(v, n - 1, visit);
        std::swap(v[n][c], n);
    }
}

// Heap's algorithm -> does not need index table
template<typename Item_t, typename Visitor_type>
void heap_r(std::vector<Item_t>& v, int n, Visitor_type& visit)
{
    int c;
    // or if (test(n)) { return; }
    if (n == 1) {
        visit(v);
        return;
    }
    for (c = 1; c <= n; ++c) {
        heap_r(v, n - 1, visit);
        auto k = n % 2 ? 1 : c;
        std::swap(k, n);
    }
}

template<typename Item_t, typename Visitor_type>
void heap_i(std::vector<Item_t>& v, int n, Visitor_type& visit)
{

    std::vector<Item_t> c(v.size(), 1);

    std::vector<Item_t> p(v.size());
    std::iota(p.begin(), p.end(), 1);

    visit(v);
    int k;
    auto i = 1;
    while (i <= n) {
        if (c[i] < i) {
            k = n % 2 ? 1 : c;
            std::swap(k, n);
            c[i]++;
            i = 1;
            visit(v);
        } else {
            c[i++] = 1;
        }
    }
}

//template<typename Item_t, typename Visitor_type>
//void improved_heap_r(std::vector<Item_t>& v, int n, Visitor_type& visit)
//{
//    int c;
//    if (n == 3) {
//        visit(v);
//        p1 = p[1];
//        p2 = p[2];
//        p3 = p[3];
//        p[2] = p1;
//        p[1] = p2;
//        visit(v);
//        p[1] = p3;
//        p[3] = p2;
//        visit(v);
//        p[1] = p1;
//        p[2] = p3;
//        visit(v);
//        p[1] = p2;
//        p[3] = p1;
//        visit(v);
//        p[1] = p3;
//        p[2] = p2;
//        visit(v);
//        return;
//    }
//    for (c = 1; c <= n; c++) {
//        improved_heap_r(v, n - 1, visit);
//        auto k = n % 2 ? 1 : c;
//        std::swap(k, n);
//    }
//}

// from fxt -> www.jjj.de/fxt
template<typename Item_t>
class Perm_heap
// Gray code for permutations.
// Algorithm following
//   B. R. Heap: "Permutations by interchanges" (1963)
{
public:
    std::vector<Item_t> _digits;  // mixed radix digits with radix = [2, 3, 4, ..., n-1, (sentinel=-1)]
    std::vector<Item_t> _permutation;  // permutation
    std::size_t _size;   // permutations of n elements
    Item_t _sw1;
    Item_t _sw2;   // indices of swapped elements

private:  // have pointer data
    Perm_heap(const Perm_heap&) = delete;

    Perm_heap& operator=(const Perm_heap&) = delete;

public:
    explicit Perm_heap(std::size_t n)
            : _size{n},
              _digits(_size, 0),
              _permutation(_size),
              _sw1{0},
              _sw2{0}
    {
        _digits[n - 1] = -1UL;  // sentinel
        std::iota(_permutation.begin(), _permutation.end(), 0);
    }

    ~Perm_heap() = default;

    const std::vector<Item_t> data() const { return _permutation; }

    bool next()
    {
        // increment mixed radix number:
        auto j = 0;
        while (_digits[j] == j + 1) {
            _digits[j] = 0;
            ++j;
        }  // can read sentinel

        // j==n-1 for last permutation:
        if (j == _size - 1) { return false; }

        auto k = j + 1;
        auto x = (k & 1 ? _digits[j] : 0);
        std::swap(_permutation[k], _permutation[x]);  // omit statement to just compute swaps
        _sw1 = k;
        _sw2 = x;

        ++_digits[j];
        return true;
    }

    void get_swap(Item_t& s1, Item_t& s2) const
    {
        s1 = _sw1;
        s2 = _sw2;
    }

    void print(bool dfz = false) const
    {
        std::cout << "[ ";
        for (auto k = 0; k < _size; ++k) {
            auto t = _permutation[k];
            if (t != 0) { std::cout << t; }
            else { std::cout << (dfz ? '.' : '0'); }
            std::cout << " ";
        }
        std::cout << "]";
    }
};

// http://introcs.cs.princeton.edu/java/23recursion/Permutations.java.html
class Permutations {
public:
    // print n! permutation of the characters of the std::string s (in order)
    static void perm1(std::string s) { perm1("", s); }

    // print n! permutation of the elements of array a (not in order)
    static void perm2(std::string s)
    {
        std::vector<char> a(s.length());
        for (auto c : s) { a.emplace_back(c); }
        perm2(a, s.size());
    }

private:
    static void perm1(std::string prefix, std::string s)
    {
        auto n = s.size();
        if (n == 0) { std::cout << prefix << "\n"; }
        else { for (std::size_t i{0}; i < n; ++i) { perm1(prefix + s[i], s.substr(0, i) + s.substr(i + 1, n)); }}
    }

    static void perm2(std::vector<char>& a, std::size_t n)
    {
        if (n == 1) {
            for (auto c : a) { std::cout << c; }
            std::cout << "\n";
            return;
        }
        for (auto i = 0; i < n; ++i) {
            std::swap(a[i], a[n - 1]);
            perm2(a, n - 1);
            std::swap(a[i], a[n - 1]);
        }
    }

    static void main(std::vector<std::string> args)
    {
        auto n = std::stoul(args[0]);
        std::string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        std::string elements{alphabet.substr(0, n)};
        perm1(elements);
        std::cout << "\n";
        perm2(elements);
    }
};

#endif // PERMUTATIONS_H
