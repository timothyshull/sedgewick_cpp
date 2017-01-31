#include "Transaction.h"
#include "Std_in.h"
#include "Stack.h"
#include "Min_pq.h"
#include "Std_out.h"

int main(int argc, char* argv[])
{
    int m{utility::str_to_num(argv[1])};
    Min_pq<Transaction> pq{m + 1};

    while (!Std_in::is_empty()) {
        std::string line{Std_in::read_line()};
        Transaction transaction{line};
        pq.insert(transaction);

        if (pq.size() > m) {
            pq.delete_min();
        }
    }

    Stack<Transaction> stack;
    for (auto transaction : pq) {
        stack.push(transaction);
    }
    for (auto transaction : stack) {
        Std_out::print_line(transaction);
    }
    return 0;
}