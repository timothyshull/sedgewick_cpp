#ifndef STOPWATCH_CPU_H
#define STOPWATCH_CPU_H

#include <chrono>

class Stopwatch_cpu {
public:
    Stopwatch_cpu();

    double elapsedTime();
private:
    const static double NANOSECONDS_PER_SECOND = 1000000000;
    const std::chrono::time_point start;
};

#endif // STOPWATCH_CPU_H
