#ifndef COLLECTED_KNUTH_MORRIS_PRATT_H
#define COLLECTED_KNUTH_MORRIS_PRATT_H

#include <string>
#include <vector>

// TODO: turn this into a template that takes a container to reduce code
// duplication
class Knuth_morris_pratt {
public:
    Knuth_morris_pratt() = default;

    Knuth_morris_pratt(const Knuth_morris_pratt&) = default;

    Knuth_morris_pratt(Knuth_morris_pratt&&) = default;

    ~Knuth_morris_pratt() = default;

    Knuth_morris_pratt& operator=(const Knuth_morris_pratt&) = default;

    Knuth_morris_pratt& operator=(Knuth_morris_pratt&&) = default;

    explicit Knuth_morris_pratt(std::string& pattern);

    Knuth_morris_pratt(std::vector<char>& pattern, int radix);

    int search(std::string& text);

    int search(std::vector<char>& text);
private:
    int _radix;
    std::vector <std::vector<int>> _dfa;
    std::vector<char> _pattern_vector;
    std::string _pattern_string;

};

#endif //COLLECTED_KNUTH_MORRIS_PRATT_H
