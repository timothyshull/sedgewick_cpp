#ifndef RABIN_KARP_H
#define RABIN_KARP_H

#include <string>

class Rabin_karp {
public:
    Rabin_karp(std::string& pat);

    int search(std::string& txt);

private:
    std::string pat;
    long patHash;
    int m;
    long q;
    int R;
    long RM;

    long hash(std::string& key, int m);

    bool check(std::string& txt, int i);

    bool check(int i);

    long longRandomPrime();

};

#endif // RABIN_KARP_H
