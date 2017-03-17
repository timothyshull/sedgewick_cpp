// Program 3.5 - Sieve of Eratosthenes
#include <iostream>
#include <vector>

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    std::vector<int> a;
    a.reserve(size);

    int i;
    for (i = 2; i < size; ++i) { a[i] = 1; }

    for (i = 2; i < size; ++i) {
        if (a[i]) {
            for (int j = i; j * i < size; ++j) { a[i * j] = 0; }
        }
    }

    for (i = 2; i < size; ++i) {
        if (a[i]) { std::cout << " " << i << "\n"; }
    }
    std::cout << "\n";

    return 0;
}