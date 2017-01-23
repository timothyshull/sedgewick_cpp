#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include <vector>
#include "Point_2d.h"
#include "Stack.h"

class Graham_scan {
public:
    Graham_scan(std::vector<Point_2d>& pts);
    std::vector<Point_2d> hull();
private:
    Stack<Point_2d> hull;
    bool isConvex();
};

#endif // GRAHAM_SCAN_H
