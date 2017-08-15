#include <cstdlib>
#include <vector>
#include "Assignment_problem.h"
#include "Std_random.h"
#include "Std_out.h"

int main(int argc, char *argv[])
{
    auto n = utility::str_to_num(argv[1]);
    auto weight = std::vector<std::vector<double>>(n, std::vector<double>(n));
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
            weight[i][j] = Std_random::uniform(900) + 100;
        }
    }

    auto assignment = Assignment_problem{weight};
    Std_out::printf("weight = %.0f\n", assignment.weight());
    Std_out::print_line();

    if (n >= 20) {
        return -1;
    }
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < n; ++j) {
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