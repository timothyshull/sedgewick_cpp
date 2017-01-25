#include "Std_in.h"
#include "Point_2d.h"
#include "Std_out.h"
#include "Graham_scan.h"

int main(int argc, char* argv[])
{
    int n{Std_in::read_int()};
    std::vector<Point_2d> points;
    points.reserve(n);
    int x;
    int y;
    for (int i{0}; i < n; ++i) {
        x = Std_in::read_int();
        y = Std_in::read_int();
        points[i] = Point_2d(x, y);
    }
    Graham_scan graham{points};
    for (auto p : graham.hull()) {
        Std_out::print_line(p);
    }
    return 0;
}