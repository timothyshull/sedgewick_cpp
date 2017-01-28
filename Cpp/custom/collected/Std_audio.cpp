#include <QIODevice>
#include <QAudioFormat>
#include <QtMath>
#include <QtEndian>
#include "Std_audio.h"

Std_audio::Generator::Generator(const QAudioFormat& format, qint64 duration, int freq, QObject* parent)
        : QIODevice{parent},
          _position{0},
          _freq{freq}
{
    if (format.isValid()) {
        generateData(format, duration);
    }
}

Std_audio::Generator::~Generator() {}

void Std_audio::Generator::start()
{
    open(QIODevice::ReadOnly);
}

void Std_audio::Generator::stop()
{
    _position = 0;
    close();
}

qint64 Std_audio::Generator::readData(char* data, qint64 max_length)
{
    qint64 length{max_length};
    qint64 total{0};
    if (!_byte_array.isEmpty()) {
        while (length - total > 0) {
            const qint64 chunk{qMin((_byte_array.size() - _position), length - total)};
            memcpy(data + total, _byte_array.constData() + _position, static_cast<std::size_t>(chunk));
            _position = (_position + chunk) % _byte_array.size();
            total += chunk;
        }
    }
    return total;
}

qint64 Std_audio::Generator::writeData(const char* data, qint64 length)
{
    Q_UNUSED(data);
    Q_UNUSED(length);
    return 0;
}

qint64 Std_audio::Generator::bytesAvailable() const
{
    return _byte_array.size() + QIODevice::bytesAvailable();
}

void Std_audio::Generator::generateData(const QAudioFormat& format, qint64 duration)
{
    const int channel_bytes{format.sampleSize() / 8};
    const int sample_bytes{format.channelCount() * channel_bytes};

    qint64 length{(format.sampleRate() * format.channelCount() * (format.sampleSize() / 8)) * duration / 100000};

    Q_ASSERT(length % sample_bytes == 0);
    Q_UNUSED(sample_bytes)

    _byte_array.resize(static_cast<int>(length));
    unsigned char* ptr{reinterpret_cast<unsigned char*>(_byte_array.data())};
    int sample_index{0};

    while (length) {
        const qreal x{qSin(2 * pi * _freq * qreal(sample_index % format.sampleRate()) / format.sampleRate())};
        for (int i{0}; i < format.channelCount(); ++i) {
            if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::UnSignedInt) {
                const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 8 && format.sampleType() == QAudioFormat::SignedInt) {
                const qint8 value{static_cast<qint8>(x * 127)};
                *reinterpret_cast<quint8*>(ptr) = value;
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::UnSignedInt) {
                quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                if (format.byteOrder() == QAudioFormat::LittleEndian) {
                    qToLittleEndian<quint16>(value, ptr);
                } else {
                    qToBigEndian<quint16>(value, ptr);
                }
            } else if (format.sampleSize() == 16 && format.sampleType() == QAudioFormat::SignedInt) {
                qint16 value{static_cast<qint16>(x * 32767)};
                if (format.byteOrder() == QAudioFormat::LittleEndian) {
                    qToLittleEndian<qint16>(value, ptr);
                } else {
                    qToBigEndian<qint16>(value, ptr);
                }
            }

            ptr += channel_bytes;
            length -= channel_bytes;
        }
        ++sample_index;
    }
}

Std_audio::Audio_proxy::Audio_proxy()
        : _device{QAudioDeviceInfo::defaultOutputDevice()},
          _buffer{_buffer_size, 0},
          _format{},
          _generator{nullptr},
          _audio_output{nullptr},
          _output{nullptr}
{
    _initialize_audio();
}

Std_audio::Audio_proxy::~Audio_proxy() {}

void Std_audio::Audio_proxy::set_frequency(int freq)
{
    if (_generator) {
        _generator->_freq = freq;
    }
}

void Std_audio::Audio_proxy::_initialize_audio()
{
    // connect(_push_timer, SIGNAL(timeout()), SLOT(_push_timer_expired()));

    _format.setSampleRate(sample_rate);
    _format.setChannelCount(_channel_count);
    _format.setSampleSize(_bits_per_sample);
    _format.setCodec(_codec);
    _format.setByteOrder(QAudioFormat::LittleEndian);
    _format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(_device);
    if (!info.isFormatSupported(_format)) {
        // qWarning() << "Default format not supported - trying to use nearest";
        _format = info.nearestFormat(_format);
    }

    if (_generator) {
        delete _generator;
    }
    _generator = new Generator(_format, _duration_seconds * 1000000, _start_freq, this);

    _create_audio_output();
}

void Std_audio::Audio_proxy::start()
{
    _audio_output->start(_generator);
}

void Std_audio::Audio_proxy::stop()
{
    _audio_output->stop();
}

void Std_audio::Audio_proxy::_create_audio_output()
{
    if (_audio_output) {
        delete _audio_output;
    }
    _audio_output = nullptr;
    _audio_output = new QAudioOutput(_device, _format, this);
    _generator->start();
    _audio_output->start(_generator);

    // qreal initial_volume{QAudio::convertVolume(_audio_output->volume(), QAudio::LinearVolumeScale, QAudio::LogarithmicVolumeScale)};
    // _volume_slider->setValue(qRound(initial_volume * 100));
}

void Std_audio::Audio_proxy::_push_timer_expired()
{
    if (_audio_output && _audio_output->state() != QAudio::StoppedState) {
        int chunks{_audio_output->bytesFree() / _audio_output->periodSize()};
        while (chunks) {
            const qint64 length{_generator->read(_buffer.data(), _audio_output->periodSize())};
            if (length) {
                _output->write(_buffer.data(), length);
            }
            if (length != _audio_output->periodSize()) {
                break;
            }
            --chunks;
        }
    }
}

void Std_audio::Audio_proxy::_toggle_mode()
{
//    _push_timer->stop();
//    _audio_output->stop();
//
//    if (_pull_mode) {
//        // push mode
//        _output = _audio_output->start();
//        _pull_mode = false;
//        _push_timer->start(20);
//    } else {
//        // pull mode
//        _pull_mode = true;
//        _audio_output->start(_generator);
//    }

}

void Std_audio::Audio_proxy::_toggle_start_stop()
{
    if (_audio_output->state() == QAudio::SuspendedState) {
        _audio_output->resume();
    } else if (_audio_output->state() == QAudio::ActiveState) {
        _audio_output->suspend();
    } else if (_audio_output->state() == QAudio::StoppedState) {
        _audio_output->resume();
    } else if (_audio_output->state() == QAudio::IdleState) {
        // no-op
    }
}

void Std_audio::init()
{
    if (_audio_proxy) {
        delete _audio_proxy;
    }
    _audio_proxy = new Audio_proxy{};
}

void Std_audio::close() {}

void Std_audio::play()
{
    if (_audio_proxy) {
        _audio_proxy->start();
    }
}

void Std_audio::note(double hz, double duration, double amplitude)
{
    if (_audio_proxy) {
        _audio_proxy->set_frequency(static_cast<int>(hz));
    }
}

//static void close()
//{
//    _line.drain();
//    _line.stop();
//}
//
//static void play(double sample)
//{
//
//    if (std::isnan(sample)) { throw utility::Illegal_argument_exception{"sample is NaN"}; }
//    if (sample < -1.0) { sample = -1.0; }
//    if (sample > +1.0) { sample = +1.0; }
//
//    short s = (short) (_max_16_bit * sample);
//    _buffer[_buffer_size++] = (char) s;
//    _buffer[_buffer_size++] = (char) (s >> 8);
//
//    if (_buffer_size >= _buffer.size()) {
//        _line.write(_buffer, 0, _buffer.size());
//        _buffer_size = 0;
//    }
//}
//
//static void play(std::vector<double>& samples)
//{
//    if (samples == nullptr) { throw utility::Null_pointer_exception{"argument to play() is null"}; }
//    for (int i = 0; i < samples.size(); i++) {
//        play(samples[i]);
//    }
//}
//
//static std::vector<double> read(std::string& filename)
//{
//    std::vector<char> data = _read_byte(filename);
//    auto n = data.size();
//    std::vector<double> d;
//    d.reserve(n / 2);
//    for (int i = 0; i < n / 2; i++) {
//        d[i] = ((short) (((data[2 * i + 1] & 0xFF) << 8) + (data[2 * i] & 0xFF))) / ((double) _max_16_bit);
//    }
//    return d;
//}
//
//static synchronized void play(std::string& filename)
//{
//    if (filename == nullptr) { throw utility::Null_pointer_exception{}; }
//
//    // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
//    try {
//        Clip clip = AudioSystem.getClip();
//        InputStream
//        is = StdAudio.
//        class.getResourceAsStream(filename);
//        AudioInputStream ais = AudioSystem.getAudioInputStream(is);
//        clip.open(ais);
//        clip.start();
//    } catch (RuntimeException e) {
//        System.out.println("could not play '" + filename + "'");
//        throw e;
//    } catch (Exception e) {
//        System.out.println("could not play '" + filename + "'");
//        e.printStackTrace();
//    }
//}
//
//static synchronized void loop(std::string& filename)
//{
//    if (filename == null) { throw utility::Null_pointer_exception{}; }
//
//    // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
//    try {
//        Clip clip = AudioSystem.getClip();
//        InputStream
//        is = StdAudio.
//        class.getResourceAsStream(filename);
//        AudioInputStream ais = AudioSystem.getAudioInputStream(is);
//        clip.open(ais);
//        clip.loop(Clip.LOOP_CONTINUOUSLY);
//    } catch (RuntimeException e) {
//        System.out.println("could not play '" + filename + "'");
//        throw e;
//    } catch (Exception e) {
//        System.out.println("could not play '" + filename + "'");
//        e.printStackTrace();
//    }
//}
//
//static void save(std::string& filename, std::vector<double> samples)
//{
//
//    // assumes 44,100 samples per second
//    // use 16-bit audio, mono, signed PCM, little Endian
//    AudioFormat format = new AudioFormat(sample_rate, 16, 1, true, false);
//    std::vector<char> data = new char[2 * samples.size()];
//    for (int i = 0; i < samples.size(); i++) {
//        int temp = (short) (samples[i] * _max_16_bit);
//        data[2 * i + 0] = (char) temp;
//        data[2 * i + 1] = (char) (temp >> 8);
//    }
//
//    // now save the file
//    try {
//        ByteArrayInputStream bais = new ByteArrayInputStream(data);
//        AudioInputStream ais = new AudioInputStream(bais, format, samples.size());
//        if (filename.endsWith(".wav") || filename.endsWith(".WAV")) {
//            AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(filename));
//        } else if (filename.endsWith(".au") || filename.endsWith(".AU")) {
//            AudioSystem.write(ais, AudioFileFormat.Type.AU, new File(filename));
//        } else {
//            throw new RuntimeException("File format not supported: " + filename);
//        }
//    } catch (IOException e) {
//        System.out.println(e);
//    }
//}
//
//static void _init()
//{
//    try {
//        // 44,100 samples per second, 16-bit audio, mono, signed PCM, little Endian
//        AudioFormat format = new AudioFormat((float) sample_rate, _bits_per_sample, 1, true, false);
//        DataLine.Info
//        info = new DataLine.Info(SourceDataLine.
//        class, format);
//
//        _line = (SourceDataLine) AudioSystem.getLine(info);
//        _line.open(format, _sample_buffer_size * _bytes_per_sample);
//
//        // the internal buffer is a fraction of the actual buffer size, this choice is arbitrary
//        // it gets divided because we can't expect the buffered data to line up exactly with when
//        // the sound card decides to push out its samples.
//        _buffer = new char[_sample_buffer_size * _bytes_per_sample / 3];
//    } catch (LineUnavailableException e) {
//        System.out.println(e.getMessage());
//    }
//
//    // no sound gets made before this call
//    _line.start();
//}
//
//static std::vector<char> _read_byte(std::string& filename)
//{
//    std::vector<char> data = null;
//    AudioInputStream ais = null;
//    try {
//
//        // try to read from file
//        File file = new File(filename);
//        if (file.exists()) {
//            ais = AudioSystem.getAudioInputStream(file);
//            int charsToRead = ais.available();
//            data = new char[charsToRead];
//            int charsRead = ais.read(data);
//            if (charsToRead != charsRead) {
//                throw new RuntimeException("read only " + charsRead + " of " + charsToRead + " chars");
//            }
//        }
//
//            // try to read from URL
//        else {
//            URL
//            url = StdAudio.
//            class.getResource(filename);
//            ais = AudioSystem.getAudioInputStream(url);
//            int charsToRead = ais.available();
//            data = new char[charsToRead];
//            int charsRead = ais.read(data);
//            if (charsToRead != charsRead) {
//                throw new RuntimeException("read only " + charsRead + " of " + charsToRead + " chars");
//            }
//        }
//    } catch (IOException e) {
//        System.out.println(e.getMessage());
//        throw new RuntimeException("Could not read " + filename);
//    } catch (UnsupportedAudioFileException e) {
//        System.out.println(e.getMessage());
//        throw new RuntimeException(filename + " in unsupported audio format");
//    }
//
//    return data;
//}
//
//static std::vector<double> note(double hz, double duration, double amplitude)
//{
//    int n{static_cast<int>(sample_rate * duration)};
//    std::vector<double> a;
//    a.reserve(static_cast<std::vector<double>::size_type>(n));
//    for (int i = 0; i <= n; i++) {
//        a[i] = amplitude * std::sin(2 * pi * i * hz / sample_rate);
//    }
//    return a;
//}