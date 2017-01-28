#include <cmath>
#include <vector>
#include "Std_audio.h"

int main(int argc, char *argv[]) {
    QCoreApplication app{argc, argv};
    app.exec();
    double freq{440.0};
    Std_audio::init();
    Std_audio::play();
//    for (int i{0}; i <= Std_audio::sample_rate; ++i) {
//        std_audio.note()
//        Std_audio::play(0.5 * std::sin(2 * Std_audio::pi * freq * i / Std_audio::sample_rate));
//    }

    std::vector<int> steps{0, 2, 4, 5, 7, 9, 11, 12};
    double hz;
    for (int i{0}; i < steps.size(); ++i) {
        hz = 440.0 * std::pow(2, steps[i] / 12.0);
        Std_audio::note(hz, 1.0, 0.5);
        std::clog << hz << "\n";
    }
    Std_audio::close();
    app.quit();
    return 0;
}
