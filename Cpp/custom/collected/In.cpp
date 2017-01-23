#include "In.h"

In::In()
{
    scanner = new Scanner(new BufferedInputStream(System.in), CHARSET_NAME);
    scanner.useLocale(LOCALE);
}

In::In(Socket& socket)
{
    if (socket == null) throw new NullPointerException("argument is null");
    try {
        InputStream is = socket.getInputStream();
        scanner = new Scanner(new BufferedInputStream(is), CHARSET_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw new IllegalArgumentException("Could not open " + socket);
    }
}

In::In(URL& url)
{
    if (url == null) throw new NullPointerException("argument is null");
    try {
        URLConnection site = url.openConnection();
        InputStream is = site.getInputStream();
        scanner = new Scanner(new BufferedInputStream(is), CHARSET_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw new IllegalArgumentException("Could not open " + url);
    }
}

In::In(std::ifstream& file)
{
    if (file == null) throw new NullPointerException("argument is null");
    try {
        // for consistency with StdIn, wrap with BufferedInputStream instead of use
        // file as argument to Scanner
        FileInputStream fis = new FileInputStream(file);
        scanner = new Scanner(new BufferedInputStream(fis), CHARSET_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw new IllegalArgumentException("Could not open " + file);
    }
}

In::In(std::string& name, std::true_type)
{
    if (name == null) throw new NullPointerException("argument is null");
    try {
        // first try to read file from local file system
        File file = new File(name);
        if (file.exists()) {
            // for consistency with StdIn, wrap with BufferedInputStream instead of use
            // file as argument to Scanner
            FileInputStream fis = new FileInputStream(file);
            scanner = new Scanner(new BufferedInputStream(fis), CHARSET_NAME);
            scanner.useLocale(LOCALE);
            return;
        }

        // next try for files included in jar
        URL url = getClass().getResource(name);

        // or URL from web
        if (url == null) {
            url = new URL(name);
        }

        URLConnection site = url.openConnection();

        // in order to set User-Agent, replace above line with these two
        // HttpURLConnection site = (HttpURLConnection) url.openConnection();
        // site.addRequestProperty("User-Agent", "Mozilla/4.76");

        InputStream is = site.getInputStream();
        scanner = new Scanner(new BufferedInputStream(is), CHARSET_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw new IllegalArgumentException("Could not open " + name);
    }
}

In::In(Scanner& scanner)
{
    if (scanner == null) throw new NullPointerException("argument is null");
    this.scanner = scanner;
}

bool In::exists()
{
    return scanner != null;
}

bool In::isEmpty()
{
    return !scanner.hasNext();
}

bool In::hasNextLine()
{
    return scanner.hasNextLine();
}

bool In::hasNextChar()
{
    scanner.useDelimiter(EMPTY_PATTERN);
    boolean result = scanner.hasNext();
    scanner.useDelimiter(WHITESPACE_PATTERN);
    return result;
}

std::string In::readLine()
{
    String line;
    try {
        line = scanner.nextLine();
    } catch (NoSuchElementException e) {
        line = null;
    }
    return line;
}

char In::readChar()
{
    scanner.useDelimiter(EMPTY_PATTERN);
    String ch = scanner.next();
    assert ch.length() == 1 : "Internal (Std)In.readChar() error!"
                              + " Please contact the authors.";
    scanner.useDelimiter(WHITESPACE_PATTERN);
    return ch.charAt(0);
}

std::string In::readAll()
{
    if (!scanner.hasNextLine())
        return "";

    String result = scanner.useDelimiter(EVERYTHING_PATTERN).next();
    // not that important to reset delimeter, since now scanner is empty
    scanner.useDelimiter(WHITESPACE_PATTERN); // but let's do it anyway
    return result;
}

std::string In::readString()
{
    return scanner.next();
}

int In::readInt()
{
    return scanner.nextInt();
}

double In::readDouble()
{
    return scanner.nextDouble();
}

float In::readFloat()
{
    return scanner.nextFloat();
}

long In::readLong()
{
    return scanner.nextLong();
}

short In::readShort()
{
    return scanner.nextShort();
}

char In::readByte()
{
    return scanner.nextByte();
}

bool In::readBoolean()
{
    String s = readString();
    if (s.equalsIgnoreCase("true")) return true;
    if (s.equalsIgnoreCase("false")) return false;
    if (s.equals("1")) return true;
    if (s.equals("0")) return false;
    throw new InputMismatchException();
}

std::vector<std::string> In::readAllStrings()
{
    String[] tokens = WHITESPACE_PATTERN.split(readAll());
    if (tokens.length == 0 || tokens[0].length() > 0)
        return tokens;
    String[] decapitokens = new String[tokens.length - 1];
    for (int i = 0; i < tokens.length - 1; i++)
        decapitokens[i] = tokens[i + 1];
    return decapitokens;
}

std::vector<std::string> In::readAllLines()
{
    ArrayList<String> lines = new ArrayList<String>();
    while (hasNextLine()) {
        lines.add(readLine());
    }
    return lines.toArray(new String[0]);
}

std::vector<int> In::readAllInts()
{
    String[] fields = readAllStrings();
    int[] vals = new int[fields.length];
    for (int i = 0; i < fields.length; i++)
        vals[i] = Integer.parseInt(fields[i]);
    return vals;
}

std::vector<long> In::readAllLongs()
{
    String[] fields = readAllStrings();
    long[] vals = new long[fields.length];
    for (int i = 0; i < fields.length; i++)
        vals[i] = Long.parseLong(fields[i]);
    return vals;
}

std::vector<double> In::readAllDoubles()
{
    String[] fields = readAllStrings();
    double[] vals = new double[fields.length];
    for (int i = 0; i < fields.length; i++)
        vals[i] = Double.parseDouble(fields[i]);
    return vals;
}

void In::close()
{
    scanner.close();
}

std::vector<int> In::readInts(std::string& filename)
{
    return new In(filename).readAllInts();
}

std::vector<double> In::readDoubles(std::string& filename)
{
    return new In(filename).readAllDoubles();
}

std::vector<std::string> In::readStrings(std::string& filename)
{
    return new In(filename).readAllStrings();
}

std::vector<int> In::readInts()
{
    return new In().readAllInts();
}

std::vector<double> In::readDoubles()
{
    return new In().readAllDoubles();
}

std::vector<std::string> In::readStrings()
{
    return new In().readAllStrings();
}
