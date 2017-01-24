#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();

    double elapsedTime();
private:
    const std::chrono::time_point start;
};

#endif // STOPWATCH_H
