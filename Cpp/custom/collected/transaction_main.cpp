int main(int argc, char *argv[]) {
    Transaction[] a = new Transaction[4];
    a[0] = new Transaction("Turing   6/17/1990  644.08");
    a[1] = new Transaction("Tarjan   3/26/2002 4121.85");
    a[2] = new Transaction("Knuth    6/14/1999  288.34");
    a[3] = new Transaction("Dijkstra 8/22/2007 2678.40");

    Std_out::print_line("Unsorted");
    for (int i = 0; i < a.length; ++i)
        Std_out::print_line(a[i]);
    Std_out::print_line();

    Std_out::print_line("Sort by date");
    Arrays.sort(a, new Transaction.WhenOrder());
    for (int i = 0; i < a.length; ++i)
        Std_out::print_line(a[i]);
    Std_out::print_line();

    Std_out::print_line("Sort by customer");
    Arrays.sort(a, new Transaction.WhoOrder());
    for (int i = 0; i < a.length; ++i)
        Std_out::print_line(a[i]);
    Std_out::print_line();

    Std_out::print_line("Sort by amount");
    Arrays.sort(a, new Transaction.HowMuchOrder());
    for (int i = 0; i < a.length; ++i)
        Std_out::print_line(a[i]);
    Std_out::print_line();
    return 0;
}