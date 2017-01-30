#ifndef SUFFIX_ARRAY_X_H
#define SUFFIX_ARRAY_X_H

#include <vector>
#include <string>

class Suffix_array_x {
public:
    Suffix_array_x() = default;

    Suffix_array_x(const Suffix_array_x&) = default;

    Suffix_array_x(Suffix_array_x&&) = default;

    ~Suffix_array_x() = default;

    Suffix_array_x& operator=(const Suffix_array_x&) = default;

    Suffix_array_x& operator=(Suffix_array_x&&) = default;

    Suffix_array_x(std::string& text);

    inline std::size_t length() const noexcept { return _size; }

    inline std::size_t size() const noexcept { return _size; }

    int index(int i);

    int lcp(int i);

    std::string select(int i);

    int rank(std::string& query);

    int rank(std::string&& query);

private:
    const static int _cutoff = 5;
    // logically const
    std::string _text;
    const std::vector<int> _index;
    const std::size_t _size;

    void _sort(int lo, int hi, int d);

    void _insertion(int lo, int hi, int d);

    bool _less(int i, int j, int d);

    void _exch(int i, int j);

    int _lcp(int i, int j);

    int operator<(std::string& query, int i);
};

#endif // SUFFIX_ARRAY_X_H
