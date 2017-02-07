// Program 3.6 - Dynamic memory allocation for an array
#include <iostream>
// #include <new>

int main(int argc, char* argv[])
{
    std::size_t size{std::stoul(argv[1])};
    int* a;
    try {
        a = new int[size];
    } catch (std::bad_alloc& e) {
        std::cout << "out of memory" << "\n";
        return 0;
    }

    // a = new (std::nothrow) int[size];
    // if (a == nullptr) {
    //     std::cout << "out of memory" << "\n";
    //     return 0;
    // }
    // ...
    return 0;
}
