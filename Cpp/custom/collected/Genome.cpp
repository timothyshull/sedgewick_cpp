#include "Genome.h"

void ::Genome::compress()
{
    Alphabet DNA = Alphabet.DNA;
    String s = BinaryStdIn.readString();
    int n = s.length();
    BinaryStdOut.write(n);

    // Write two-bit code for char.
    for (int i = 0; i < n; i++) {
        int d = DNA.toIndex(s.charAt(i));
        BinaryStdOut.write(d, 2);
    }
    BinaryStdOut.close();
}

void ::Genome::expand()
{
    Alphabet DNA = Alphabet.DNA;
    int n = BinaryStdIn.readInt();
    // Read two bits; write char.
    for (int i = 0; i < n; i++) {
        char c = BinaryStdIn.readChar(2);
        BinaryStdOut.write(DNA.toChar(c), 8);
    }
    BinaryStdOut.close();
}
