#include "Stopwatch.h"

Stopwatch::Stopwatch() : _start{std::chrono::system_clock::now()} {}

double Stopwatch::elapsed_time()
{
    auto int_start{_start.time_since_epoch().count()};
    std::chrono::system_clock::time_point now{std::chrono::system_clock::now()};
    auto int_now{now.time_since_epoch().count()};
    return (int_now - int_start) / 1000.0;
}
