
int main(int argc, char *argv[]) {
    In in;
    String urlName = "http://introcs.cs.princeton.edu/stdlib/InTest.txt";

    // read from a URL
    System.out.println("readAll() from URL " + urlName);
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        System.out.println(in.readAll());
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();

    // read one line at a time from URL
    System.out.println("readLine() from URL " + urlName);
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        while (!in.isEmpty()) {
            String s = in.readLine();
            System.out.println(s);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();

    // read one string at a time from URL
    System.out.println("readString() from URL " + urlName);
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In(urlName);
        while (!in.isEmpty()) {
            String s = in.readString();
            System.out.println(s);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();


    // read one line at a time from file in current directory
    System.out.println("readLine() from current directory");
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In("./InTest.txt");
        while (!in.isEmpty()) {
            String s = in.readLine();
            System.out.println(s);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();


    // read one line at a time from file using relative path
    System.out.println("readLine() from relative path");
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In("../stdlib/InTest.txt");
        while (!in.isEmpty()) {
            String s = in.readLine();
            System.out.println(s);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();

    // read one char at a time
    System.out.println("readChar() from file");
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In("InTest.txt");
        while (!in.isEmpty()) {
            char c = in.readChar();
            System.out.print(c);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();
    System.out.println();

    // read one line at a time from absolute OS X / Linux path
    System.out.println("readLine() from absolute OS X / Linux path");
    System.out.println("---------------------------------------------------------------------------");
    in = new In("/n/fs/introcs/www/java/stdlib/InTest.txt");
    try {
        while (!in.isEmpty()) {
            String s = in.readLine();
            System.out.println(s);
        }
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();


    // read one line at a time from absolute Windows path
    System.out.println("readLine() from absolute Windows path");
    System.out.println("---------------------------------------------------------------------------");
    try {
        in = new In("G:\\www\\introcs\\stdlib\\InTest.txt");
        while (!in.isEmpty()) {
            String s = in.readLine();
            System.out.println(s);
        }
        System.out.println();
    } catch (Exception e) {
        System.out.println(e);
    }
    System.out.println();
    return 0;
}
