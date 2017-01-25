#include <cmath>
#include <vector>
#include "Std_audio.h"

int main(int argc, char *argv[]) {
    double freq{440.0};
    for (int i{0}; i <= Std_audio::SAMPLE_RATE; ++i) {
        Std_audio::play(0.5 * std::sin(2 * Std_audio::pi * freq * i / Std_audio::SAMPLE_RATE));
    }

    std::vector<int> steps{0, 2, 4, 5, 7, 9, 11, 12};
    double hz;
    for (int i{0}; i < steps.size(); ++i) {
        hz = 440.0 * std::pow(2, steps[i] / 12.0);
        Std_audio::play(Std_audio::note(hz, 1.0, 0.5));
    }
    Std_audio::close();
    return 0;
}
