#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <string>
#include <vector>

class Suffix_array;

class Suffix {
public:
    Suffix() = default;

    Suffix(const Suffix&) = default;

    Suffix(Suffix&&) = default;

    ~Suffix() = default;

    Suffix& operator=(const Suffix&) = default;

    Suffix& operator=(Suffix&&) = default;

    Suffix(std::string& text, int index);

    bool operator<(const Suffix& rhs) const;

    inline bool operator==(const Suffix& rhs) const { return _text == rhs._text && _index == rhs._index; };

    inline std::string to_string() const { return {_text.begin() + _index, _text.end()}; }

private:
    const std::string _text;
    const int _index;

    inline std::size_t _length() const { return _text.size() - _index; }

    inline std::size_t _size() const { return _text.size() - _index; }

    inline char operator[](int i) const { return _text[this->_index + i]; }

    friend class Suffix_array;
};

class Suffix_array {
public:
    Suffix_array() = default;

    Suffix_array(const Suffix_array&) = default;

    Suffix_array(Suffix_array&&) = default;

    ~Suffix_array() = default;

    Suffix_array& operator=(const Suffix_array&) = default;

    Suffix_array& operator=(Suffix_array&&) = default;

    Suffix_array(std::string& text);

    inline std::size_t length() const { return _suffixes.size(); }

    inline std::size_t size() const { return _suffixes.size(); }

    int index(int i);

    int lcp(int i);

    std::string select(int i);

    int rank(std::string& query);

    int rank(std::string&& query);

private:
    std::vector<Suffix> _suffixes;

    int _lcp(Suffix& s, Suffix& t);

    bool operator<(std::string& query, Suffix& suffix);
};

#endif // SUFFIX_ARRAY_H
