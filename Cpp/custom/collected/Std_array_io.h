#ifndef STD_ARRAY_IO_H
#define STD_ARRAY_IO_H

#include <vector>
#include <deque>

namespace Std_array_io {
    std::vector<double> readDouble1D();

    void print(std::vector<double>& a);

    std::vector<std::vector<double>> readDouble2D();

    void print(std::vector<std::vector<double>>& a);

    std::vector<int> readInt1D();

    void print(std::vector<int>& a);

    std::vector<std::vector<int>> readInt2D();

    void print(std::vector<std::vector<int>>& a);

    void print(std::deque<bool>& a);

    std::vector<std::deque<bool>> readBoolean2D();

    void print(std::vector<std::deque<bool>>& a);
};

#endif // STD_ARRAY_IO_H
