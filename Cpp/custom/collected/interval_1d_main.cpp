#include <vector>
#include "Interval_1d.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<Interval_1d> intervals;
    intervals.reserve(4);
    intervals.emplace_back(15.0, 33.0);
    intervals.emplace_back(45.0, 60.0);
    intervals.emplace_back(20.0, 70.0);
    intervals.emplace_back(46.0, 55.0);

    Std_out::print_line("Unsorted:");
    for (auto i : intervals) {
        Std_out::print_line(i);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by min endpoint:");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::min_endpoint_order);
    for (auto i : intervals) {
        Std_out::print_line(i);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by max endpoint:");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::max_endpoint_order);
    for (auto i : intervals) {
        Std_out::print_line(i);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by length:");
    std::sort<Interval_1d>(intervals.begin(), intervals.end(), Interval_1d::length_order);
    for (auto i : intervals) {
        Std_out::print_line(i);
    }
    Std_out::print_line();
    return 0;
}