int main(int argc, char* argv[])
{
    Interval1D[]
    intervals = new Interval1D[4];
    intervals[0] = new Interval1D(15.0, 33.0);
    intervals[1] = new Interval1D(45.0, 60.0);
    intervals[2] = new Interval1D(20.0, 70.0);
    intervals[3] = new Interval1D(46.0, 55.0);

    Std_out::print_line("Unsorted");
    for (int i = 0; i < intervals.length; ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by min endpoint");
    Arrays.sort(intervals, Interval1D.MIN_ENDPOINT_ORDER);
    for (int i = 0; i < intervals.length; ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by max endpoint");
    Arrays.sort(intervals, Interval1D.MAX_ENDPOINT_ORDER);
    for (int i = 0; i < intervals.length; ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by length");
    Arrays.sort(intervals, Interval1D.LENGTH_ORDER);
    for (int i = 0; i < intervals.length; ++i) {
        Std_out::print_line(intervals[i]);
    }
    Std_out::print_line();
    return 0;
}