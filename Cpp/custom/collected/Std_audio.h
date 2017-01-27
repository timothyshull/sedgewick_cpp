#ifndef STD_AUDIO_H
#define STD_AUDIO_H

class Std_audio {
public:
    const static int pi = 3.14159265358979323846;

public static final int SAMPLE_RATE = 44100;

private static final int BYTES_PER_SAMPLE = 2;                // 16-bit audio
private static final int BITS_PER_SAMPLE = 16;                // 16-bit audio
private static final double MAX_16_BIT = Short.MAX_VALUE;     // 32,767
private static final int SAMPLE_BUFFER_SIZE = 4096;


private static SourceDataLine line;   // to play the sound
private static byte[] buffer;         // our internal buffer
private static int bufferSize = 0;    // number of samples currently in internal buffer

private StdAudio() {
        // can not instantiate
    }

    // static initializer
    static {
        init();
    }

    // open up an audio stream
private static void init() {
        try {
            // 44,100 samples per second, 16-bit audio, mono, signed PCM, little Endian
            AudioFormat format = new AudioFormat((float) SAMPLE_RATE, BITS_PER_SAMPLE, 1, true, false);
            DataLine.Info info = new DataLine.Info(SourceDataLine.class, format);

            line = (SourceDataLine) AudioSystem.getLine(info);
            line.open(format, SAMPLE_BUFFER_SIZE * BYTES_PER_SAMPLE);

            // the internal buffer is a fraction of the actual buffer size, this choice is arbitrary
            // it gets divided because we can't expect the buffered data to line up exactly with when
            // the sound card decides to push out its samples.
            buffer = new byte[SAMPLE_BUFFER_SIZE * BYTES_PER_SAMPLE / 3];
        } catch (LineUnavailableException e) {
            System.out.println(e.getMessage());
        }

        // no sound gets made before this call
        line.start();
    }


    /**
     * Closes standard audio.
     */
public static void close() {
        line.drain();
        line.stop();
    }

    /**
     * Writes one sample (between -1.0 and +1.0) to standard audio.
     * If the sample is outside the range, it will be clipped.
     *
     * @param sample the sample to play
     * @throws IllegalArgumentException if the sample is <tt>Double.NaN</tt>
     */
public static void play(double sample) {

        // clip if outside [-1, +1]
        if (Double.isNaN(sample)) throw new IllegalArgumentException("sample is NaN");
        if (sample < -1.0) sample = -1.0;
        if (sample > +1.0) sample = +1.0;

        // convert to bytes
        short s = (short) (MAX_16_BIT * sample);
        buffer[bufferSize++] = (byte) s;
        buffer[bufferSize++] = (byte) (s >> 8);   // little Endian

        // send to sound card if buffer is full
        if (bufferSize >= buffer.length) {
            line.write(buffer, 0, buffer.length);
            bufferSize = 0;
        }
    }

    /**
     * Writes the array of samples (between -1.0 and +1.0) to standard audio.
     * If a sample is outside the range, it will be clipped.
     *
     * @param samples the array of samples to play
     * @throws IllegalArgumentException if any sample is <tt>Double.NaN</tt>
     */
public static void play(double[] samples) {
        if (samples == null) throw new NullPointerException("argument to play() is null");
        for (int i = 0; i < samples.length; i++) {
            play(samples[i]);
        }
    }

    /**
     * Reads audio samples from a file (in .wav or .au format) and returns
     * them as a double array with values between -1.0 and +1.0.
     *
     * @param filename the name of the audio file
     * @return the array of samples
     */
public static double[] read(String filename) {
        byte[] data = readByte(filename);
        int n = data.length;
        double[] d = new double[n / 2];
        for (int i = 0; i < n / 2; i++) {
            d[i] = ((short) (((data[2 * i + 1] & 0xFF) << 8) + (data[2 * i] & 0xFF))) / ((double) MAX_16_BIT);
        }
        return d;
    }

    /**
     * Plays an audio file (in .wav, .mid, or .au format) in a background thread.
     *
     * @param filename the name of the audio file
     */
public static synchronized void play(String filename) {
        if (filename == null) throw new NullPointerException();

        // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
        try {
            Clip clip = AudioSystem.getClip();
            InputStream is = StdAudio.class.getResourceAsStream(filename);
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

    /**
     * Loops an audio file (in .wav, .mid, or .au format) in a background thread.
     *
     * @param filename the name of the audio file
     */
public static synchronized void loop(String filename) {
        if (filename == null) throw new NullPointerException();

        // code adapted from: http://stackoverflow.com/questions/26305/how-can-i-play-sound-in-java
        try {
            Clip clip = AudioSystem.getClip();
            InputStream is = StdAudio.class.getResourceAsStream(filename);
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

    // return data as a byte array
private static byte[] readByte(String filename) {
        byte[] data = null;
        AudioInputStream ais = null;
        try {

            // try to read from file
            File file = new File(filename);
            if (file.exists()) {
                ais = AudioSystem.getAudioInputStream(file);
                int bytesToRead = ais.available();
                data = new byte[bytesToRead];
                int bytesRead = ais.read(data);
                if (bytesToRead != bytesRead)
                    throw new RuntimeException("read only " + bytesRead + " of " + bytesToRead + " bytes");
            }

                // try to read from URL
            else {
                URL url = StdAudio.class.getResource(filename);
                ais = AudioSystem.getAudioInputStream(url);
                int bytesToRead = ais.available();
                data = new byte[bytesToRead];
                int bytesRead = ais.read(data);
                if (bytesToRead != bytesRead)
                    throw new RuntimeException("read only " + bytesRead + " of " + bytesToRead + " bytes");
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


    /**
     * Saves the double array as an audio file (using .wav or .au format).
     *
     * @param filename the name of the audio file
     * @param samples  the array of samples
     */
public static void save(String filename, double[] samples) {

        // assumes 44,100 samples per second
        // use 16-bit audio, mono, signed PCM, little Endian
        AudioFormat format = new AudioFormat(SAMPLE_RATE, 16, 1, true, false);
        byte[] data = new byte[2 * samples.length];
        for (int i = 0; i < samples.length; i++) {
            int temp = (short) (samples[i] * MAX_16_BIT);
            data[2 * i + 0] = (byte) temp;
            data[2 * i + 1] = (byte) (temp >> 8);
        }

        // now save the file
        try {
            ByteArrayInputStream bais = new ByteArrayInputStream(data);
            AudioInputStream ais = new AudioInputStream(bais, format, samples.length);
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


    /***************************************************************************
     * Unit tests <tt>StdAudio</tt>.
     ***************************************************************************/

    // create a note (sine wave) of the given frequency (Hz), for the given
    // duration (seconds) scaled to the given volume (amplitude)
private static double[] note(double hz, double duration, double amplitude) {
        int n = (int) (StdAudio.SAMPLE_RATE * duration);
        double[] a = new double[n + 1];
        for (int i = 0; i <= n; i++)
            a[i] = amplitude * Math.sin(2 * Math.PI * i * hz / StdAudio.SAMPLE_RATE);
        return a;
    }
};

#endif // STD_AUDIO_H
