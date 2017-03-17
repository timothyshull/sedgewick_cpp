#include "Multiway_merge.h"

int main(int argc, char* argv[])
{
    std::size_t n{static_cast<std::size_t>(argc)};
    std::vector<In> streams;
    streams.reserve(n);
    for (int i{0}; i < n; ++i) {
        streams[i] = In{argv[i]};
    }
    Multiway_merge::merge(streams);
    return 0;
}