#include "Std_out.h"
#include "Std_in.h"
#include "Point_2d.h"
#include "Closest_pair.h"

int main(int argc, char* argv[])
{
    int n{Std_in::read_int()};
    std::vector<Point_2d> points;
    points.reserve(n);
    double x;
    double y;
    for (int i = 0; i < n; ++i) {
        x = Std_in::read_double();
        y = Std_in::read_double();
        points[i] = Point_2d{x, y};
    }
    Closest_pair closest{points};
    std::stringstream ss;
    ss << closest.distance() << " from " << closest.either() << " to " << closest.other();
    Std_out::print_line(ss.str());
    return 0;
}
