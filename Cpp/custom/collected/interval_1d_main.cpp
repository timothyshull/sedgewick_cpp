#include <vector>
#include "Interval_1d.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<Interval_1d> intervals;
    intervals.reserve(4);
    intervals[0] = Interval_1d(15.0, 33.0);
    intervals[1] = Interval_1d(45.0, 60.0);
    intervals[2] = Interval_1d(20.0, 70.0);
    intervals[3] = Interval_1d(46.0, 55.0);

    Std_out::print_line("Unsorted");
    for (int i = 0; i < intervals.size(); ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by min endpoint");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::MIN_ENDPOINT_ORDER);
    for (int i = 0; i < intervals.size(); ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by max endpoint");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::MAX_ENDPOINT_ORDER);
    for (int i = 0; i < intervals.size(); ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by length");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::LENGTH_ORDER);
    for (int i = 0; i < intervals.size(); ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();
    return 0;
}