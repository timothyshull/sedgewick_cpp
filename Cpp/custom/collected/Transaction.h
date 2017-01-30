#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include "Date.h"

class Transaction;

struct Who_order {
    inline bool operator<(const Transaction& v, const Transaction& w) const noexcept { return v._who < w._who; };
};

struct When_order {
    inline bool operator<(const Transaction& v, const Transaction& w) const noexcept { return v._when < w._when; };
};

struct How_much_order {
    inline bool operator<(const Transaction& v, const Transaction& w) const noexcept { return v._amount < w._amount; };
};

class Transaction {
public:
    Transaction(std::string& who, Date& when, double amount);

    Transaction(std::string& transaction);

    inline std::string who() const noexcept { return _who; }

    inline Date when() const { return _when; }

    inline double amount() const noexcept { return _amount; }

    inline std::string to_string() const { return "Transaction(" + _who + _when.to_string() + std::to_string(_amount) + ")"; }

    inline bool operator<(const Transaction& rhs) const noexcept { return _amount < rhs._amount; };

    bool operator==(const Transaction& rhs) const noexcept { return _amount == rhs._amount && _who == rhs._who && _when == rhs._when; }

    std::size_t hash_code();

private:
    const std::string _who;
    const Date _when;
    const double _amount;

    Transaction(std::tuple<std::string, Date, double>&& args);

    static std::tuple<std::string, Date, double> _prep_args(std::string& transaction);

    friend class Who_order;

    friend class When_order;

    friend class How_much_order;
};

#endif // TRANSACTION_H
