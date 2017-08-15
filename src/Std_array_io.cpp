#include "Std_array_io.h"
#include "Std_out.h"
#include "Std_in.h"

std::vector<double> Std_array_io::read_double1D()
{
    auto n = Std_in::read_int();
    std::vector<double> a;
    a.reserve(static_cast<std::vector<double>::size_type>(n));
    for (auto i = 0; i < n; ++i) {
        a[i] = Std_in::read_double();
    }
    return a;
}

void ::Std_array_io::print(std::vector<double>& a)
{
    auto n = a.size();
    Std_out::print_line(n);
    for (auto i = 0; i < n; ++i) {
        Std_out::printf("%9.5f ", a[i]);
    }
    Std_out::print_line();
}

std::vector<std::vector<double>> Std_array_io::read_double2D()
{
    auto m = Std_in::read_int();
    auto n = Std_in::read_int();
    std::vector<std::vector<double>> a;
    a.reserve(static_cast<std::vector<std::vector<double>>::size_type>(m));
    for (auto i = 0; i < m; ++i) {
        a[i] = std::vector<double>{static_cast<std::vector<double>::size_type>(n)};
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_double();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<double>>& a)
{
    auto m = a.size();
    auto n = a[0].size();
    Std_out::print_line(m + " " + n);
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            Std_out::printf("%9.5f ", a[i][j]);
        }
        Std_out::print_line();
    }
}

std::vector<int> Std_array_io::read_int1D()
{
    auto n = Std_in::read_int();
    std::vector<int> a;
    a.reserve(static_cast<std::vector<int>::size_type>(n));
    for (auto i = 0; i < n; ++i) {
        a[i] = Std_in::read_int();
    }
    return a;
}

void ::Std_array_io::print(std::vector<int>& a)
{
    auto n = a.size();
    Std_out::print_line(n);
    for (auto i = 0; i < n; ++i) {
        Std_out::printf("%9d ", a[i]);
    }
    Std_out::print_line();
}

std::vector<std::vector<int>> Std_array_io::read_int2D()
{
    auto m = Std_in::read_int();
    auto n = Std_in::read_int();
    std::vector<std::vector<int>> a;
    a.reserve(m);
    for (auto i = 0; i < m; ++i) {
        a[i].reserve(n);
    }
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_int();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<int>>& a)
{
    auto m = a.size();
    auto n = a[0].size();
    Std_out::print_line(m + " " + n);
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            Std_out::printf("%9d ", a[i][j]);
        }
        Std_out::print_line();
    }
}

void ::Std_array_io::print(std::deque<bool>& a)
{
    auto n = a.size();
    Std_out::print_line(n);
    for (auto i = 0; i < n; ++i) {
        if (a[i]) { Std_out::print("1 "); }
        else { Std_out::print("0 "); }
    }
    Std_out::print_line();
}

std::vector<std::deque<bool>> Std_array_io::read_boolean2D()
{
    auto m = Std_in::read_int();
    auto n = Std_in::read_int();
    std::vector<std::deque<bool>> a;
    a.reserve(static_cast<std::vector<std::deque<bool>>::size_type>(m));
    for (auto i = 0; i < m; ++i) {
        a[i] = std::deque<bool>{static_cast<std::deque<bool>::size_type>(n)};
        for (auto j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_boolean();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::deque<bool>>& a)
{
    auto m = a.size();
    auto n = a[0].size();
    Std_out::print_line(m + " " + n);
    for (auto i = 0; i < m; ++i) {
        for (auto j = 0; j < n; ++j) {
            if (a[i][j]) { Std_out::print("1 "); }
            else { Std_out::print("0 "); }
        }
        Std_out::print_line();
    }
}
