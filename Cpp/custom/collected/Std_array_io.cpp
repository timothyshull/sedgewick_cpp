#include "Std_array_io.h"
#include "Std_out.h"

std::vector<double> Std_array_io::read_double1D()
{
    int n = Std_in::read_int();
    std::vector<double> a = new double[n];
    for (int i = 0; i < n; ++i) {
        a[i] = Std_in::read_double();
    }
    return a;
}

void ::Std_array_io::print(std::vector<double>& a)
{
    int n = a.length;
    Std_out::print_line(n);
    for (int i = 0; i < n; ++i) {
        Std_out::printf("%9.5f ", a[i]);
    }
    Std_out::print_line();
}

std::vector<std::vector<double>> Std_array_io::read_double2D()
{
    int m = Std_in::read_int();
    int n = Std_in::read_int();
    std::vector<std::vector<double>> a = new double[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_double();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<double>>& a)
{
    int m = a.length;
    int n = a[0].length;
    Std_out::print_line(m + " " + n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            Std_out::printf("%9.5f ", a[i][j]);
        }
        Std_out::print_line();
    }
}

std::vector<int> Std_array_io::read_int1D()
{
    int n = Std_in::read_int();
    std::vector<int> a = new int[n];
    for (int i = 0; i < n; ++i) {
        a[i] = Std_in::read_int();
    }
    return a;
}

void ::Std_array_io::print(std::vector<int>& a)
{
    int n = a.length;
    Std_out::print_line(n);
    for (int i = 0; i < n; ++i) {
        Std_out::printf("%9d ", a[i]);
    }
    Std_out::print_line();
}

std::vector<std::vector<int>> Std_array_io::read_int2D()
{
    int m = Std_in::read_int();
    int n = Std_in::read_int();
    std::vector<std::vector<int>> a;
    a.reserve(m);
    for (int i = 0; i < m; ++i) {
        a[i].reserve(n);
    }
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_int();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<int>>& a)
{
    int m = a.length;
    int n = a[0].length;
    Std_out::print_line(m + " " + n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            Std_out::printf("%9d ", a[i][j]);
        }
        Std_out::print_line();
    }
}

void ::Std_array_io::print(std::deque<bool>& a)
{
    int n = Std_in::read_int();
    std::deque<bool> a = new boolean[n];
    for (int i = 0; i < n; ++i) {
        a[i] = Std_in::read_boolean();
    }
    return a;
}

std::vector<std::deque<bool>> Std_array_io::read_boolean2D()
{
    int m = Std_in::read_int();
    int n = Std_in::read_int();
    std::deque<bool>[] a = new boolean[m][n];
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            a[i][j] = Std_in::read_boolean();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::deque<bool>>& a)
{
    int m = a.length;
    int n = a[0].length;
    Std_out::print_line(m + " " + n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[i][j]) Std_out::print("1 ");
            else Std_out::print("0 ");
        }
        Std_out::print_line();
    }
}
