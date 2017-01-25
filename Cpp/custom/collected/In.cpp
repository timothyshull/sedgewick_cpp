#include "In.h"

In::In()
{
    scanner = new Scanner(new BufferedInputStream(System.in), CHARSet_NAME);
    scanner.useLocale(LOCALE);
}

In::In(Socket& socket)
{
    if (socket == null) throw new NullPointerException("argument is null");
    try {
        InputStream is = socket.getInputStream();
        scanner = new Scanner(new BufferedInputStream(is), CHARSet_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw utility::Illegal_argument_exception("Could not open " + socket);
    }
}

In::In(URL& url)
{
    if (url == null) throw new NullPointerException("argument is null");
    try {
        URLConnection site = url.openConnection();
        InputStream is = site.getInputStream();
        scanner = new Scanner(new BufferedInputStream(is), CHARSet_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw utility::Illegal_argument_exception("Could not open " + url);
    }
}

In::In(std::ifstream& file)
{
    if (file == null) throw new NullPointerException("argument is null");
    try {
        // for consistency with StdIn, wrap with BufferedInputStream instead of use
        // file as argument to Scanner
        FileInputStream fis = new FileInputStream(file);
        scanner = new Scanner(new BufferedInputStream(fis), CHARSet_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw utility::Illegal_argument_exception("Could not open " + file);
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
            scanner = new Scanner(new BufferedInputStream(fis), CHARSet_NAME);
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
        scanner = new Scanner(new BufferedInputStream(is), CHARSet_NAME);
        scanner.useLocale(LOCALE);
    } catch (IOException ioe) {
        throw utility::Illegal_argument_exception("Could not open " + name);
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

bool In::is_empty()
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
    bool result = scanner.hasNext();
    scanner.useDelimiter(WHITESPACE_PATTERN);
    return result;
}

std::string In::read_line()
{
    std::string line;
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
    std::string ch = scanner.next();
    assert ch.length() == 1 : "Internal (Std)In.readChar() error!"
                              + " Please contact the authors.";
    scanner.useDelimiter(WHITESPACE_PATTERN);
    return ch.charAt(0);
}

std::string In::readAll()
{
    if (!scanner.hasNextLine())
        return "";

    std::string result = scanner.useDelimiter(EVERYTHING_PATTERN).next();
    // not that important to reset delimeter, since now scanner is empty
    scanner.useDelimiter(WHITESPACE_PATTERN); // but let's do it anyway
    return result;
}

std::string In::read_string()
{
    return scanner.next();
}

int In::read_int()
{
    return scanner.nextInt();
}

double In::read_double()
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

bool In::read_boolean()
{
    std::string s = read_string();
    if (s.equalsIgnoreCase("true")) return true;
    if (s.equalsIgnoreCase("false")) return false;
    if (s.equals("1")) return true;
    if (s.equals("0")) return false;
    throw new InputMismatchException();
}

std::vector<std::string> In::readAllStrings()
{
    std::vector<std::string> tokens = WHITESPACE_PATTERN.split(readAll());
    if (tokens.size() == 0 || tokens[0].length() > 0)
        return tokens;
    std::vector<std::string> decapitokens = new String[tokens.size() - 1];
    for (int i = 0; i < tokens.size() - 1; ++i)
        decapitokens[i] = tokens[i + 1];
    return decapitokens;
}

std::vector<std::string> In::readAllLines()
{
    ArrayList<std::string> lines = new ArrayList<std::string>();
    while (hasNextLine()) {
        lines.add(read_line());
    }
    return lines.toArray(new String[0]);
}

std::vector<int> In::readAllInts()
{
    std::vector<std::string> fields = readAllStrings();
    std::vector<int> vals = new int[fields.length];
    for (int i = 0; i < fields.length; ++i)
        vals[i] = utility::str_to_num(fields[i]);
    return vals;
}

std::vector<long> In::readAllLongs()
{
    std::vector<std::string> fields = readAllStrings();
    long[] vals = new long[fields.length];
    for (int i = 0; i < fields.length; ++i)
        vals[i] = Long.parseLong(fields[i]);
    return vals;
}

std::vector<double> In::readAllDoubles()
{
    std::vector<std::string> fields = readAllStrings();
    std::vector<double> vals = new double[fields.length];
    for (int i = 0; i < fields.length; ++i)
        vals[i] = Double.parseDouble(fields[i]);
    return vals;
}

void In::close()
{
    scanner.close();
}

std::vector<int> In::read_ints(std::string& filename)
{
    return new In(filename).readAllInts();
}

std::vector<double> In::read_doubles(std::string& filename)
{
    return new In(filename).readAllDoubles();
}

std::vector<std::string> In::read_strings(std::string& filename)
{
    return new In(filename).readAllStrings();
}

std::vector<int> In::read_ints()
{
    return new In().readAllInts();
}

std::vector<double> In::read_doubles()
{
    return new In().readAllDoubles();
}

std::vector<std::string> In::read_strings()
{
    return new In().readAllStrings();
}
