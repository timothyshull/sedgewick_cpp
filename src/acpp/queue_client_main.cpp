// Program 4.20 - Queue client program (queue simulation)
#include <iostream>
#include <vector>
#include <random>

#include "Linked_list_queue.h"

int main(int argc, char* argv[])
{
    static const int max_size = 4;
    std::random_device rd;
    std::default_random_engine gen{rd()};
    std::uniform_int_distribution<> dis{0, std::numeric_limits<int>::max()};

    auto size = std::stoi(argv[1]);
    std::vector<Queue<int>> queues(max_size);

    int in;
    int out;
    for (auto i = 0; i < size; ++i, std::cout << "\n") {
        in = dis(gen) % max_size;
        out = dis(gen) % max_size;
        queues[in].put(i);
        std::cout << i << " in ";
        if (!queues[out].empty()) {
            std::cout << queues[out].get() << " out";
        }
        std::cout << "\n";
        for (int k = 0; k < max_size; ++k, std::cout << "\n") {
            Queue<int> q = queues[k];
            std::cout << k << ": ";
            while (!q.empty()) {
                std::cout << q.get() << " ";
            }
        }
    }
    return 0;
}

