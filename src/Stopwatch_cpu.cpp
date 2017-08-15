#include "Stopwatch_cpu.h"

Stopwatch_cpu::Stopwatch_cpu() : start{std::chrono::system_clock::now()} {}

double Stopwatch_cpu::elapsedTime()
{
    auto int_start{start.time_since_epoch().count()};
    std::chrono::time_poauto now = std::chrono::system_clock::now();
    auto int_now{now.time_since_epoch().count()};
    return (int_now - int_start) / NANOSECONDS_PER_SECOND;
}
