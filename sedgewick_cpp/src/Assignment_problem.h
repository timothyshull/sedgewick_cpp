#ifndef ASSIGNMENT_PROBLEM_H
#define ASSIGNMENT_PROBLEM_H

#include <vector>

class Assignment_problem {
public:
    Assignment_problem() = default;

    Assignment_problem(const Assignment_problem&) = default;

    Assignment_problem(Assignment_problem&&) = default;

    ~Assignment_problem() = default;

    Assignment_problem& operator=(Assignment_problem&) = default;

    Assignment_problem& operator=(Assignment_problem&&) = default;

    Assignment_problem(std::vector<std::vector<double>>& weight);

    double dual_row(int i) const;

    double dual_col(int j) const;

    int solution(int i) const;

    double weight() const;

private:
    static const int _unmatched = -1;
    int _dimension;
    std::vector<std::vector<double>> _weight;
    double _min_weight;
    std::vector<double> _px;
    std::vector<double> _py;
    std::vector<int> _xy;
    std::vector<int> _yx;

    void _augment();

    double _reduced_cost(int i, int j) const;

    void _validate(int i) const;

    bool _is_dual_feasible() const;

    bool _is_complementary_slack() const;

    bool _is_perfect_matching() const;

    bool _certify_solution() const;
};

#endif // ASSIGNMENT_PROBLEM_H
