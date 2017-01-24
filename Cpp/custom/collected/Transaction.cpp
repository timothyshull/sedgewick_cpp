#include "Transaction.h"

bool Who_order::operator<(Transaction& v, Transaction& w)
{
    return v.who < w.who;
}

bool When_order::operator<(Transaction& v, Transaction& w)
{
    return v.when < w.when;
}

bool How_much_order::operator<(Transaction& v, Transaction& w)
{
    return v.amount < w.amount;
}

Transaction::Transaction(std::string& who, Date& when, double amount)
{
    if (Double.isNaN(amount) || Double.isInfinite(amount))
        throw new IllegalArgumentException("Amount cannot be NaN or infinite");
    this.who = who;
    this.when = when;
    this.amount = amount;
}

Transaction::Transaction(std::string& transaction)
{
    String[] a = transaction.split("\\s+");
    who = a[0];
    when = new Date(a[1]);
    amount = Double.parseDouble(a[2]);
    if (Double.isNaN(amount) || Double.isInfinite(amount))
        throw new IllegalArgumentException("Amount cannot be NaN or infinite");
}

std::string Transaction::who()
{
    return who;
}

Date Transaction::when()
{
    return when;
}

double Transaction::amount()
{
    return amount;
}

std::string Transaction::to_string()
{
    return String.format("%-10s %10s %8.2f", who, when, amount);
}

bool Transaction::operator<(Transaction& rhs)
{
    return Double.compare(this.amount, that.amount)
}

bool Transaction::operator==(Transaction& rhs)
{
    if (other == this) return true;
    if (other == null) return false;
    if (other.getClass() != this.getClass()) return false;
    Transaction that = (Transaction) other;
    return (this.amount == that.amount) && (this.who.equals(that.who))
           && (this.when.equals(that.when));
}

int Transaction::hashCode()
{
    int hash = 1;
    hash = 31 * hash + who.hashCode();
    hash = 31 * hash + when.hashCode();
    hash = 31 * hash + ((Double) amount).hashCode();
    return hash;
}
