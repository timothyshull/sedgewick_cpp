#include "Std_audio.h"

static void close()
{
    _line.drain();
    _line.stop();
}

static void play(double sample)
{

    if (std::isnan(sample)) { throw utility::Illegal_argument_exception{"sample is NaN"}; }
    if (sample < -1.0) { sample = -1.0; }
    if (sample > +1.0) { sample = +1.0; }

    short s = (short) (_max_16_bit * sample);
    _buffer[_buffer_size++] = (char) s;
    _buffer[_buffer_size++] = (char) (s >> 8);

    if (_buffer_size >= _buffer.size()) {
        _line.write(_buffer, 0, _buffer.size());
        _buffer_size = 0;
    }
}

static void play(std::vector<double>& samples)
{
    if (samples == nullptr) { throw utility::Null_pointer_exception{"argument to play() is null"}; }
    for (int i = 0; i < samples.size(); i++) {
        play(samples[i]);
    }
}

static std::vector<double> read(std::string& filename)
{
    std::vector<char> data = _read_byte(filename);
    auto n = data.size();
    std::vector<double> d;
    d.reserve(n / 2);
    for (int i = 0; i < n / 2; i++) {
        d[i] = ((short) (((data[2 * i + 1] & 0xFF) << 8) + (data[2 * i] & 0xFF))) / ((double) _max_16_bit);
    }
    return d;
}

static synchronized void play(std::string& filename)
{
    if (filename == nullptr) { throw utility::Null_pointer_exception{}; }

    // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
    try {
        Clip clip = AudioSystem.getClip();
        InputStream
        is = StdAudio.
        class.getResourceAsStream(filename);
        AudioInputStream ais = AudioSystem.getAudioInputStream(is);
        clip.open(ais);
        clip.start();
    } catch (RuntimeException e) {
        System.out.println("could not play '" + filename + "'");
        throw e;
    } catch (Exception e) {
        System.out.println("could not play '" + filename + "'");
        e.printStackTrace();
    }
}

static synchronized void loop(std::string& filename)
{
    if (filename == null) { throw utility::Null_pointer_exception{}; }

    // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
    try {
        Clip clip = AudioSystem.getClip();
        InputStream
        is = StdAudio.
        class.getResourceAsStream(filename);
        AudioInputStream ais = AudioSystem.getAudioInputStream(is);
        clip.open(ais);
        clip.loop(Clip.LOOP_CONTINUOUSLY);
    } catch (RuntimeException e) {
        System.out.println("could not play '" + filename + "'");
        throw e;
    } catch (Exception e) {
        System.out.println("could not play '" + filename + "'");
        e.printStackTrace();
    }
}

static void save(std::string& filename, std::vector<double> samples)
{

    // assumes 44,100 samples per second
    // use 16-bit audio, mono, signed PCM, little Endian
    AudioFormat format = new AudioFormat(sample_rate, 16, 1, true, false);
    std::vector<char> data = new char[2 * samples.size()];
    for (int i = 0; i < samples.size(); i++) {
        int temp = (short) (samples[i] * _max_16_bit);
        data[2 * i + 0] = (char) temp;
        data[2 * i + 1] = (char) (temp >> 8);
    }

    // now save the file
    try {
        ByteArrayInputStream bais = new ByteArrayInputStream(data);
        AudioInputStream ais = new AudioInputStream(bais, format, samples.size());
        if (filename.endsWith(".wav") || filename.endsWith(".WAV")) {
            AudioSystem.write(ais, AudioFileFormat.Type.WAVE, new File(filename));
        } else if (filename.endsWith(".au") || filename.endsWith(".AU")) {
            AudioSystem.write(ais, AudioFileFormat.Type.AU, new File(filename));
        } else {
            throw new RuntimeException("File format not supported: " + filename);
        }
    } catch (IOException e) {
        System.out.println(e);
    }
}

static void _init()
{
    try {
        // 44,100 samples per second, 16-bit audio, mono, signed PCM, little Endian
        AudioFormat format = new AudioFormat((float) sample_rate, _bits_per_sample, 1, true, false);
        DataLine.Info
        info = new DataLine.Info(SourceDataLine.
        class, format);

        _line = (SourceDataLine) AudioSystem.getLine(info);
        _line.open(format, _sample_buffer_size * _bytes_per_sample);

        // the internal buffer is a fraction of the actual buffer size, this choice is arbitrary
        // it gets divided because we can't expect the buffered data to line up exactly with when
        // the sound card decides to push out its samples.
        _buffer = new char[_sample_buffer_size * _bytes_per_sample / 3];
    } catch (LineUnavailableException e) {
        System.out.println(e.getMessage());
    }

    // no sound gets made before this call
    _line.start();
}

static std::vector<char> _read_byte(std::string& filename)
{
    std::vector<char> data = null;
    AudioInputStream ais = null;
    try {

        // try to read from file
        File file = new File(filename);
        if (file.exists()) {
            ais = AudioSystem.getAudioInputStream(file);
            int charsToRead = ais.available();
            data = new char[charsToRead];
            int charsRead = ais.read(data);
            if (charsToRead != charsRead) {
                throw new RuntimeException("read only " + charsRead + " of " + charsToRead + " chars");
            }
        }

            // try to read from URL
        else {
            URL
            url = StdAudio.
            class.getResource(filename);
            ais = AudioSystem.getAudioInputStream(url);
            int charsToRead = ais.available();
            data = new char[charsToRead];
            int charsRead = ais.read(data);
            if (charsToRead != charsRead) {
                throw new RuntimeException("read only " + charsRead + " of " + charsToRead + " chars");
            }
        }
    } catch (IOException e) {
        System.out.println(e.getMessage());
        throw new RuntimeException("Could not read " + filename);
    } catch (UnsupportedAudioFileException e) {
        System.out.println(e.getMessage());
        throw new RuntimeException(filename + " in unsupported audio format");
    }

    return data;
}

static std::vector<double> note(double hz, double duration, double amplitude)
{
    int n{static_cast<int>(sample_rate * duration)};
    std::vector<double> a;
    a.reserve(static_cast<std::vector<double>::size_type>(n));
    for (int i = 0; i <= n; i++) {
        a[i] = amplitude * std::sin(2 * pi * i * hz / sample_rate);
    }
    return a;
}