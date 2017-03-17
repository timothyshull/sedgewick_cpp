#include "Counter.h"
#include "Std_random.h"
#include "Interval_1d.h"
#include "Interval_2d.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    double x_min{utility::str_to_num<double>(argv[1])};
    double x_max{utility::str_to_num<double>(argv[2])};
    double y_min{utility::str_to_num<double>(argv[3])};
    double y_max{utility::str_to_num<double>(argv[4])};
    int trials{utility::str_to_num<int>(argv[5])};

    Interval_1d x_interval{x_min, x_max};
    Interval_1d y_interval{y_min, y_max};
    Interval_2d box{x_interval, y_interval};
    box.draw();

    Counter counter{"hits"};
    double x;
    double y;
    for (int t{0}; t < trials; ++t) {
        x = Std_random::uniform(0.0, 1.0);
        y = Std_random::uniform(0.0, 1.0);
        Point_2d point = Point_2d{x, y};

        if (box.contains(point)) {
            counter.increment();
        } else {
            point.draw();
        }
    }

    Std_out::print_line(counter);
    Std_out::printf("box area = %.2f\n", box.area());
    return 0;
}