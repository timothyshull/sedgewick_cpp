#ifndef ALPHABET_H
#define ALPHABET_H

#include <vector>
#include <string>

class Alphabet {
    std::vector<char> _alphabet;
    std::vector<int> _inverse;
    int _radix = 255;

public:
    explicit Alphabet(std::string alpha);

    explicit Alphabet(int radix);

    inline bool contains(char c) const { return _inverse[c] != -1; };

    inline int radix() const { return _radix; }

    int lg_r() const;

    inline int to_index(char c) const { return _inverse[c]; }

    std::vector<int> to_indices(std::string s) const;

    inline char to_char(int index) const { return _alphabet[index]; };

    std::string to_chars(std::vector<int> indices) const;

};

namespace Alphabets {
    static const Alphabet binary{"01"};

    static const Alphabet octal{"01234567"};

    static const Alphabet decimal{"0123456789"};

    static const Alphabet hexadecimal{"0123456789ABCDEF"};

    static const Alphabet dna{"ACGT"};

    static const Alphabet lowercase{"abcdefghijklmnopqrstuvwxyz"};

    static const Alphabet uppercase{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

    static const Alphabet protein{"ACDEFGHIKLMNPQRSTVWY"};

    static const Alphabet base64{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

    static const Alphabet ascii{128};

    static const Alphabet extended_ascii{256};

    static const Alphabet unicode16{65536};
}

#endif // ALPHABET_H
