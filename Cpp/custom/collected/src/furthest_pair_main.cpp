#include "Std_in.h"
#include "Point_2d.h"
#include "Std_out.h"
#include "Furthest_pair.h"

int main(int argc, char* argv[])
{
    int n = Std_in::read_int();
    std::vector<Point_2d> points;
    points.reserve(static_cast<std::vector<Point_2d>::size_type>(n));
    int x;
    int y;
    for (int i{0}; i < n; ++i) {
        x = Std_in::read_int();
        y = Std_in::read_int();
        points[i] = Point_2d(x, y);
    }
    Furthest_pair furthest_pair{points};
    std::stringstream ss;
    ss << furthest_pair.distance() << " from " << furthest_pair.either().to_string() << " to " << furthest_pair.other().to_string();
    Std_out::print_line(ss.str());
    return 0;
}