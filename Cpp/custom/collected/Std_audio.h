#ifndef STD_AUDIO_H
#define STD_AUDIO_H

#include <limits>
#include <vector>
#include <cmath>

#include "utility.h"

class Std_audio {
public:
    const static double pi = 3.14159265358979323846;

    static const int sample_rate = 44100;

    void close();

    void play();

    void init();

    static void play(double sample);

    static void play(std::vector<double>& samples);

    static std::vector<double> read(std::string& filename);

    static void play(std::string& filename);

    static void loop(std::string& filename);

    static void save(std::string& filename, std::vector<double> samples);

    void note(double hz, double duration, double amplitude);

private:
    static const int _bytes_per_sample = 2;
    static const int _bits_per_sample = 16;
    static const int _channel_count = 1;
    static const int _sample_buffer_size = 4096;
    static const char* _codec = "audio/pcm";
    static const double _max_16_bit = std::numeric_limits<short>::max();
    char *_buffer;
    int _buffer_size = 0;

    static std::vector<char> _read_byte(std::string& filename);
};

#endif // STD_AUDIO_H
