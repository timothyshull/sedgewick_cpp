#include "Genome.h"
#include "Binary_std_out.h"
#include "Binary_std_in.h"
#include "Alphabet.h"

void Genome::compress()
{
    Alphabet dna{Alphabets::dna};
    std::string s{Binary_std_in::read_string()};
    auto n = s.size();
    Binary_std_out::write(n);

    for (int i{0}; i < n; ++i) {
        int d{dna.to_index(s[i])};
        Binary_std_out::write(d, 2);
    }
    Binary_std_out::close();
}

void Genome::expand()
{
    Alphabet dna{Alphabets::dna};
    int n{Binary_std_in::read_int()};
    for (int i{0}; i < n; ++i) {
        char c{Binary_std_in::read_char(2)};
        Binary_std_out::write(dna.to_char(c), 8);
    }
    Binary_std_out::close();
}
