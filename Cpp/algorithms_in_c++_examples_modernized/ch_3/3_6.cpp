#include<iostream>
#include<memory>
#include<vector>

using std::cin;
using std::cout;
using std::unique_ptr;
using std::vector;

int main(int argc, char* argv[])
{
    int i;
    int n = atoi(argv[1]);
    std::unique_ptr<vector<int>> a{new vector<int>{n}};
    if (a == nullptr) {
        cout << "out of memory" << "\n";
        return -1;
    }
    // ...
    return 0;
}
