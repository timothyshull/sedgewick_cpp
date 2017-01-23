#ifndef DATE_H
#define DATE_H

#include <vector>

class Date {
public:
    Date(int month, int day, int year);
    Date(std::string& date);
    int month();
    int day();
    int year();
    Date next();
    bool isAfter(Date& that);
    bool isBefore(Date& that);


    std::string toString();

    bool operator<(Date& rhs);
    bool operator=(Date& rhs);
    int hashCode();
private:
    const static std::vector<int> DAYS{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    const int month;
    const int day;
    const int year;

    bool isValid(int m, int d, int y);
    bool isLeapYear(int y);
};

#endif // DATE_H
