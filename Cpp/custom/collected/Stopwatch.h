#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <chrono>

class Stopwatch {
public:
    Stopwatch();

    double elapsed_time();

private:
    const std::chrono::system_clock::time_point _start;
};

#endif // STOPWATCH_H
