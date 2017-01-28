#ifndef STD_AUDIO_H
#define STD_AUDIO_H

#include <limits>
#include <vector>
#include <cmath>

#include <QtCore/QCoreApplication>
#include <QAudioOutput>
#include <QIODevice>
#include <QTimer>

#include "utility.h"

namespace Std_audio {
    class Audio_proxy;

    class Generator : public QIODevice {
    Q_OBJECT

    public:
        Generator(const QAudioFormat& format, qint64 duration, int sample_rate_hz, QObject* parent);

        ~Generator();

        void start();

        void stop();

        qint64 readData(char* data, qint64 max_length);

        qint64 writeData(const char* data, qint64 len);

        qint64 bytesAvailable() const;

    private:
        void generateData(const QAudioFormat& format, qint64 duration);

    private:
        qint64 _position;
        QByteArray _byte_array;
        int _freq;

        friend class Audio_proxy;
    };

    class Audio_proxy : public QObject {
    Q_OBJECT
    public:
        Audio_proxy();

        ~Audio_proxy();

        void start();

        void stop();

        void set_frequency(int freq);

    private:
        static const int _sample_buffer_size = 4096;
        static const bool _pull_mode = true;
        static const int _start_freq = 440;
        static const int _duration_seconds = 1;
        static const int _buffer_size = 32768;

        QTimer* _push_timer;

        QByteArray _buffer;
        QAudioFormat _format;
        Generator* _generator;
        QAudioOutput* _audio_output;
        QIODevice* _output;
        QAudioDeviceInfo _device;

        // QCoreApplication _app;
        // static int _buffer_size = 0;

        void _initialize_audio();

        void _create_audio_output();

    private slots:

        void _push_timer_expired();

        void _toggle_mode();

        void _toggle_start_stop();
    };

    static const int _bytes_per_sample = 2;

    static const int _bits_per_sample = 16;

    static const int _channel_count = 1;

    static const char* _codec = "audio/pcm";

    static const double _max_16_bit = std::numeric_limits<short>::max();

    static Audio_proxy* _audio_proxy;

    const static double pi = 3.14159265358979323846;

    static const int sample_rate = 44100;

    void close();

    void play();

    void init();

    // static void play(double sample);

    // static void play(std::vector<double>& samples);

    // static std::vector<double> read(std::string& filename);

    // static void play(std::string& filename);

    // static void loop(std::string& filename);

    // static void save(std::string& filename, std::vector<double> samples);

    void note(double hz, double duration, double amplitude);

    // static std::vector<char> _read_byte(std::string& filename);

};

#endif // STD_AUDIO_H
