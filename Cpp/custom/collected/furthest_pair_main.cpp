#include "Std_in.h"
#include "Point_2d.h"
#include "Std_out.h"
#include "Furthest_pair.h"

int main(int argc, char* argv[])
{
    int n = Std_in::read_int();
    std::vector<Point_2d> points;
    points.reserve(n);
    int x;
    int y;
    for (int i = 0; i < n; ++i) {
        x = Std_in::read_int();
        y = Std_in::read_int();
        points[i] = Point_2d(x, y);
    }
    Furthest_pair furthest_pair{points};
    Std_out::print_line(furthest_pair.distance() + " from " + furthest_pair.either() + " to " + furthest_pair.other());
    return 0;
}