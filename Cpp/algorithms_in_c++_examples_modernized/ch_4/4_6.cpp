#include <iostream>
#include <string.h>
#include "STACK.cxx"

using std::cout;

int main(int argc, char* argv[])
{
    char* a = argv[1];
    int N = strlen(a);
    STACK<char> ops(N);
    for (int i = 0; i < N; i++) {
        if (a[i] == ')') {
            cout << ops.pop() << " ";
        }
        if ((a[i] == '+') || (a[i] == '*')) {
            ops.push(a[i]);
        }
        if ((a[i] >= '0') && (a[i] <= '9')) {
            cout << a[i] << " ";
        }
    }
    cout << "\n";
    return 0;
}

