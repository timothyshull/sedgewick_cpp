#include "Transaction.h"
#include "utility.h"

Transaction::Transaction(std::string& who, Date& when, double amount)
        : _who{who},
          _when{when},
          _amount{amount}
{
    if (std::isnan(amount) || std::isinf(amount)) {
        throw utility::Illegal_argument_exception("Amount cannot be NaN or infinite");
    }
}

Transaction::Transaction(std::string&& who, Date&& when, double amount)
        : _who{who},
          _when{when},
          _amount{amount}
{
    if (std::isnan(amount) || std::isinf(amount)) {
        throw utility::Illegal_argument_exception("Amount cannot be NaN or infinite");
    }
}

Transaction::Transaction(std::string& transaction) : Transaction{_prep_args(transaction)}
{
    if (std::isnan(_amount) || std::isinf(_amount)) {
        throw utility::Illegal_argument_exception("Amount cannot be NaN or infinite");
    }
}

Transaction::Transaction(std::string&& transaction) : Transaction{_prep_args(transaction)}
{
    if (std::isnan(_amount) || std::isinf(_amount)) {
        throw utility::Illegal_argument_exception("Amount cannot be NaN or infinite");
    }
}

std::size_t Transaction::hash_code()
{
    std::size_t hash = 1;
    hash = 31 * hash + std::hash<std::string>{}(_who);
    hash = 31 * hash + _when.hash_code();
    hash = 31 * hash + std::hash<double>{}(_amount);
    return hash;
}

Transaction::Transaction(std::tuple<std::string, Date, double>&& args)
        : _who{std::get<0>(args)},
          _when{std::get<1>(args)},
          _amount{std::get<2>(args)} {}

std::tuple<std::string, Date, double> Transaction::_prep_args(std::string& transaction)
{
    std::vector<std::string> a;
    utility::split_string(transaction, ' ', a);
    std::string who{a[0]};
    Date when = Date(a[1]);
    double amount{utility::str_to_num<double>(a[2].c_str())};
    return {who, when, amount};
}
