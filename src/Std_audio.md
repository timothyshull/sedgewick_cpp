pi
sample_rate
Std_audio
close
play
play
read
play
loop
save
_bytes_per_sample
_bits_per_sample
_max_16_bit
_sample_buffer_size
_line
_buffer
_buffer_size
_app
- _init
    - setup QCoreApplication, pass argc, argv
    - setup sub object, initializeAudio in ctor
    - call app.exec()
_read_byte
note


# Generator : QIODevice
- ctor(const QAudioFormat& format, qint64 durationUs, int sampleRate, QObject* parent)
- qint64 readData(char* data, qint64 maxlen);
- qint64 writeData(const char* data, qint64 len);
- qint64 bytesAvailable() const;
## private
- void generateData(const QAudioFormat& format, qint64 durationUs, int sampleRate);
- m_pos
- m_buffer

# AudioTest
- ctor initializeAudio
- initializeAudio (_init)
- createAudioOutput ()