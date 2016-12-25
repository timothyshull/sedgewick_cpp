#include <iostream>

using std::cin;
using std::cout;

int main(int argc, char* argv[])
{
    int i, N = atoi(argv[1]);
    int* a = new int[N];
    if (a == 0) {
        cout << "out of memory" << "\n";
        return 0;
    }
    // ...
    return 0;
}
