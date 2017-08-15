#include "Transaction.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    std::vector<Transaction> a;
    a.reserve(4);
    a.emplace_back("Turing   6/17/1990  644.08");
    a.emplace_back("Tarjan   3/26/2002 4121.85");
    a.emplace_back("Knuth    6/14/1999  288.34");
    a.emplace_back("Dijkstra 8/22/2007 2678.40");

    Std_out::print_line("Unsorted");
    for (auto i = 0; i < a.size(); ++i) {
        Std_out::print_line(a[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by date");
    std::sort(a.begin(), a.end(), Transaction::When_order{});
    for (auto i = 0; i < a.size(); ++i) {
        Std_out::print_line(a[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by customer");
    std::sort(a.begin(), a.end(), Transaction::Who_order{});
    for (auto i = 0; i < a.size(); ++i) {
        Std_out::print_line(a[i]);
    }
    Std_out::print_line();

    Std_out::print_line("Sort by amount");
    std::sort(a.begin(), a.end(), Transaction::How_much_order{});
    for (auto i = 0; i < a.size(); ++i) {
        Std_out::print_line(a[i]);
    }
    Std_out::print_line();
    return 0;
}