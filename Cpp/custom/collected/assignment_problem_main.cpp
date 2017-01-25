#include <cstdlib>
#include <vector>
#include "Assignment_problem.h"
#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int n = utility::str_to_num(argv[1]);
    std::vector<std::vector<double>> weight;
    weight.reserve(n);
    for (auto v : weight) {
        v.reserve(n);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            weight[i][j] = Std_random::uniform(900) + 100;
        }
    }

    Assignment_problem assignment{weight};
    Std_out::printf("weight = %.0f\n", assignment.weight());
    Std_out::print_line();

    if (n >= 20) { return -1; }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == assignment.solution(i)) {
                Std_out::printf("*%.0f ", weight[i][j]);
            } else {
                Std_out::printf(" %.0f ", weight[i][j]);
            }
        }
        Std_out::print_line();
    }
    return 0;
}