#include "Stopwatch.h"

Stopwatch::Stopwatch() : start{std::chrono::system_clock::now()} {}

double Stopwatch::elapsedTime()
{
    auto int_start{start.time_since_epoch().count()};
    std::chrono::time_point now{std::chrono::system_clock::now()};
    auto int_now{now.time_since_epoch().count()};
    return (int_now - int_start) / 1000.0;
}
