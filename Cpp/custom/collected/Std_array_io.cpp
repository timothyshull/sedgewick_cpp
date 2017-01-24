#include "Std_array_io.h"

std::vector<double> Std_array_io::readDouble1D()
{
    int n = StdIn.readInt();
    double[] a = new double[n];
    for (int i = 0; i < n; i++) {
        a[i] = StdIn.readDouble();
    }
    return a;
}

void ::Std_array_io::print(std::vector<double>& a)
{
    int n = a.length;
    StdOut.println(n);
    for (int i = 0; i < n; i++) {
        StdOut.printf("%9.5f ", a[i]);
    }
    StdOut.println();
}

std::vector<std::vector<double>> Std_array_io::readDouble2D()
{
    int m = StdIn.readInt();
    int n = StdIn.readInt();
    double[][] a = new double[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = StdIn.readDouble();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<double>>& a)
{
    int m = a.length;
    int n = a[0].length;
    StdOut.println(m + " " + n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            StdOut.printf("%9.5f ", a[i][j]);
        }
        StdOut.println();
    }
}

std::vector<int> Std_array_io::readInt1D()
{
    int n = StdIn.readInt();
    int[] a = new int[n];
    for (int i = 0; i < n; i++) {
        a[i] = StdIn.readInt();
    }
    return a;
}

void ::Std_array_io::print(std::vector<int>& a)
{
    int n = a.length;
    StdOut.println(n);
    for (int i = 0; i < n; i++) {
        StdOut.printf("%9d ", a[i]);
    }
    StdOut.println();
}

std::vector<std::vector<int>> Std_array_io::readInt2D()
{
    int m = StdIn.readInt();
    int n = StdIn.readInt();
    int[][] a = new int[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = StdIn.readInt();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::vector<int>>& a)
{
    int m = a.length;
    int n = a[0].length;
    StdOut.println(m + " " + n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            StdOut.printf("%9d ", a[i][j]);
        }
        StdOut.println();
    }
}

void ::Std_array_io::print(std::deque<bool>& a)
{
    int n = StdIn.readInt();
    boolean[] a = new boolean[n];
    for (int i = 0; i < n; i++) {
        a[i] = StdIn.readBoolean();
    }
    return a;
}

std::vector<std::deque<bool>> Std_array_io::readBoolean2D()
{
    int m = StdIn.readInt();
    int n = StdIn.readInt();
    boolean[][] a = new boolean[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = StdIn.readBoolean();
        }
    }
    return a;
}

void ::Std_array_io::print(std::vector<std::deque<bool>>& a)
{
    int m = a.length;
    int n = a[0].length;
    StdOut.println(m + " " + n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (a[i][j]) StdOut.print("1 ");
            else StdOut.print("0 ");
        }
        StdOut.println();
    }
}
