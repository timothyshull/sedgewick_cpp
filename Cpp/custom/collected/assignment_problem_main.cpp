
#include <cstdlib>
#include <vector>

int main(int argc, char* argv[])
{
    int n = std::atoi(argv[1]);
    std::vector<std::vector<double>> weight;
    weight.reserve(static_cast<std::vector<std::vector<double>>::size_type>(n));
    for (auto v : weight) {
        v.reserve(static_cast<std::vector<double>::size_type>(n));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            weight[i][j] = StdRandom.uniform(900) + 100;
        }
    }

    AssignmentProblem assignment{weight};
    StdOut.printf("weight = %.0f\n", assignment.weight());
    StdOut.println();

    // print n-by-n matrix and optimal solution
    if (n >= 20) { return -1; }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j == assignment.sol(i)) {
                StdOut.printf("*%.0f ", weight[i][j]);
            } else {
                StdOut.printf(" %.0f ", weight[i][j]);
            }
        }
        StdOut.println();
    }
    return 0;
}