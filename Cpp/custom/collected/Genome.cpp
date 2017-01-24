#include "Genome.h"

void ::Genome::compress()
{
    Alphabet DNA = Alphabet.DNA;
    std::string s = Binary_std_in::read_string();
    int n = s.length();
    Binary_std_out::write(n);

    // Write two-bit code for char.
    for (int i = 0; i < n; ++i) {
        int d = DNA.toIndex(s.charAt(i));
        Binary_std_out::write(d, 2);
    }
    Binary_std_out::close();
}

void ::Genome::expand()
{
    Alphabet DNA = Alphabet.DNA;
    int n = Binary_std_in::read_int();
    // Read two bits; write char.
    for (int i = 0; i < n; ++i) {
        char c = Binary_std_in::readChar(2);
        Binary_std_out::write(DNA.toChar(c), 8);
    }
    Binary_std_out::close();
}
