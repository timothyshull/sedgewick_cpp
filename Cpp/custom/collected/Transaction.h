#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"

class Transaction;

struct Who_order {
    bool operator<(Transaction& v, Transaction& w);
};

struct When_order {
    bool operator<(Transaction& v, Transaction& w);
};

struct How_much_order {
    bool operator<(Transaction& v, Transaction& w);
};

class Transaction {
public:
    Transaction(std::string& who, Date& when, double amount);

    Transaction(std::string& transaction);

    std::string who();

    Date when();

    double amount();

    std::string to_string();

    bool operator<(Transaction& rhs);

    bool operator==(Transaction& rhs);

    int hashCode();

private:
    const std::string who;
    const Date when;
    const double amount;

    friend class Who_order;

    friend class When_order;

    friend class How_much_order;
};

#endif // TRANSACTION_H
