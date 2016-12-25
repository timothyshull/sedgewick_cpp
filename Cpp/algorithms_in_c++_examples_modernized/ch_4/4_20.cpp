#include <iostream>
#include <stdlib.h>
#include "QUEUE.cxx"

using std::cout;

static const int M = 4;

int main(int argc, char* argv[])
{
    int N = atoi(argv[1]);
    QUEUE<int> queues[M];
    for (int i = 0; i < N; i++, cout << "\n") {
        int in = rand() % M, out = rand() % M;
        queues[in].put(i);
        cout << i << " in ";
        if (!queues[out].empty()) {
            cout << queues[out].get() << " out";
        }
        cout << "\n";
        for (int k = 0; k < M; k++, cout << "\n") {
            QUEUE<int> q = queues[k];
            cout << k << ": ";
            while (!q.empty()) {
                cout << q.get() << " ";
            }
        }
    }
    return 0;
}

