
int main(int argc, char *argv[]) {
    In in;
    std::string urlName = "http://introcs.cs.princeton.edu/stdlib/InTest.txt";

    // read from a URL
    System.out.print_line("readAll() from URL " + urlName);
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        System.out.print_line(in.readAll());
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();

    // read one line at a time from URL
    System.out.print_line("read_line() from URL " + urlName);
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        while (!in.is_empty()) {
            std::string s = in.read_line();
            System.out.print_line(s);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();

    // read one string at a time from URL
    System.out.print_line("read_string() from URL " + urlName);
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        while (!in.is_empty()) {
            std::string s = in.read_string();
            System.out.print_line(s);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();


    // read one line at a time from file in current directory
    System.out.print_line("read_line() from current directory");
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In("./InTest.txt");
        while (!in.is_empty()) {
            std::string s = in.read_line();
            System.out.print_line(s);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();


    // read one line at a time from file using relative path
    System.out.print_line("read_line() from relative path");
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In("../stdlib/InTest.txt");
        while (!in.is_empty()) {
            std::string s = in.read_line();
            System.out.print_line(s);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();

    // read one char at a time
    System.out.print_line("readChar() from file");
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In("InTest.txt");
        while (!in.is_empty()) {
            char c = in.readChar();
            System.out.print(c);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();
    System.out.print_line();

    // read one line at a time from absolute OS X / Linux path
    System.out.print_line("read_line() from absolute OS X / Linux path");
    System.out.print_line("---------------------------------------------------------------------------");
    in = new In("/n/fs/introcs/www/java/stdlib/InTest.txt");
    try {
        while (!in.is_empty()) {
            std::string s = in.read_line();
            System.out.print_line(s);
        }
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();


    // read one line at a time from absolute Windows path
    System.out.print_line("read_line() from absolute Windows path");
    System.out.print_line("---------------------------------------------------------------------------");
    try {
        in = new In("G:\\www\\introcs\\stdlib\\InTest.txt");
        while (!in.is_empty()) {
            std::string s = in.read_line();
            System.out.print_line(s);
        }
        System.out.print_line();
    } catch (Exception e) {
        System.out.print_line(e);
    }
    System.out.print_line();
    return 0;
}
