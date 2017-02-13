#include <deque>
#include <gsl/gsl_util>

#include "Assignment_problem.h"
#include "utility.h"
#include "Edge_weighted_digraph.h"
#include "Std_out.h"

Assignment_problem::Assignment_problem(std::vector<std::vector<double>>& weight)
        : _dimension(gsl::narrow<int, std::vector<std::vector<double>>::size_type>(weight.size())),
          _weight(weight.size()),
          _min_weight{0},
          _px(weight.size()),
          _py(weight.size()),
          _xy(weight.size()),
          _yx(weight.size())
{
    for (int i{0}; i < _dimension; ++i) {
        for (int j{0}; j < _dimension; ++j) {
            if (weight[i][j] < _min_weight) {
                _min_weight = weight[i][j];
            }
            _weight[i][j] = _weight[i][j];
        }
    }

    for (int i{0}; i < _dimension; ++i) {
        _xy[i] = _unmatched;
    }
    for (int j{0}; j < _dimension; ++j) {
        _yx[j] = _unmatched;
    }

    for (int k{0}; k < _dimension; ++k) {
        utility::alg_assert(_is_dual_feasible(), "Assignment_problem _is_dual_feasible _check failed");
        utility::alg_assert(_is_complementary_slack(), "Assignment_problem _is_complementary_slack _check failed");
        _augment();
    }
    utility::alg_assert(_certify_solution(), "Assignment_problem _certify_solution _check failed");
}

double Assignment_problem::dual_row(int i) const
{
    _validate(i);
    return _px[i];
}

double Assignment_problem::dual_col(int j) const
{
    _validate(j);
    return _py[j];
}

int Assignment_problem::solution(int i) const
{
    _validate(i);
    return _xy[i];
}

double Assignment_problem::weight() const
{
    double total = 0.0;
    for (int i{0}; i < _dimension; ++i) {
        if (_xy[i] != _unmatched) {
            total += _weight[i][_xy[i]];
        }
    }
    return total;
}

void Assignment_problem::_augment()
{
    Edge_weighted_digraph g{2 * _dimension + 2};
    int s = 2 * _dimension;
    int t = 2 * _dimension + 1;
    for (int i{0}; i < _dimension; ++i) {
        if (_xy[i] == _unmatched) {
            Directed_edge e{s, i, 0.0};
            g.add_edge(e);
        }
    }
    for (int j{0}; j < _dimension; ++j) {
        if (_yx[j] == _unmatched) {
            Directed_edge e{_dimension + j, t, _py[j]};
            g.add_edge(e);
        }
    }
    for (int i{0}; i < _dimension; ++i) {
        for (int j{0}; j < _dimension; ++j) {
            if (_xy[i] == j) {
                Directed_edge e{_dimension + j, i, 0.0};
                g.add_edge(e);
            } else {
                Directed_edge e{i, _dimension + j, _reduced_cost(i, j)};
                g.add_edge(e);
            }
        }
    }

    Dijkstra_sp spt{g, s};

    for (auto e : spt.path_to(t)) {
        int i = e.from();
        int j = e.to() - _dimension;
        if (i < _dimension) {
            _xy[i] = j;
            _yx[j] = i;
        }
    }

    // update dual variables
    for (int i{0}; i < _dimension; ++i) {
        _px[i] += spt.distance_to(i);
    }
    for (int j{0}; j < _dimension; ++j) {
        _py[j] += spt.dist_to(_dimension + j);
    }
}

double Assignment_problem::_reduced_cost(int i, int j) const
{
    return (_weight[i][j] - _min_weight) + _px[i] - _py[j];
}

void Assignment_problem::_validate(int i) const
{
    if (i < 0 || i >= _dimension) {
        throw utility::Index_out_of_bounds_exception("");
    }
}

bool Assignment_problem::_is_dual_feasible() const
{
    for (int i{0}; i < _dimension; ++i) {
        for (int j{0}; j < _dimension; ++j) {
            if (_reduced_cost(i, j) < 0) {
                Std_out::print_line("Dual variables are not feasible");
                return false;
            }
        }
    }
    return true;
}

bool Assignment_problem::_is_complementary_slack() const
{
    for (int i{0}; i < _dimension; ++i) {
        if ((_xy[i] != _unmatched) && (_reduced_cost(i, _xy[i]) != 0)) {
            Std_out::print_line("Primal and dual variables are not complementary slack");
            return false;
        }
    }
    return true;
}

bool Assignment_problem::_is_perfect_matching() const
{
    std::deque<bool> perm{};
    perm.resize(_dimension);
    for (int i{0}; i < _dimension; ++i) {
        if (perm[_xy[i]]) {
            Std_out::print_line("Not a perfect matching");
            return false;
        }
        perm[_xy[i]] = true;
    }

    for (int j{0}; j < _dimension; ++j) {
        if (_xy[_yx[j]] != j) {
            Std_out::print_line("xy[] and _yx[] are not inverses");
            return false;
        }
    }
    for (int i{0}; i < _dimension; ++i) {
        if (_yx[_xy[i]] != i) {
            Std_out::print_line("xy[] and _yx[] are not inverses");
            return false;
        }
    }

    return true;
}

bool Assignment_problem::_certify_solution() const
{
    return _is_perfect_matching() && _is_dual_feasible() && _is_complementary_slack();
}
