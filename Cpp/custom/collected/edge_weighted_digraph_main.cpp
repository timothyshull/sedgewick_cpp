#include<fstream>

#include"Edge_weighted_digraph.h"

int main(int argc, char *argv[]) {
    std::fstream in{argv[1]};
    Edge_weighted_digraph g{in};

    std::cout << g << "\n";
    return 0;
}
