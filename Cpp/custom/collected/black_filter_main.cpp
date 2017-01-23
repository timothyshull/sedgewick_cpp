

int main(int argc, char* argv[])
{
    SET <String> set = new SET<String>();

    // read in strings and add to set
    In in = new In(args[0]);
    while (!in.isEmpty()) {
        String word = in.readString();
        set.add(word);
    }

    // read in string from standard input, printing out all exceptions
    while (!StdIn.isEmpty()) {
        String word = StdIn.readString();
        if (!set.contains(word)) {
            StdOut.println(word);
        }
    }
    return 0;
}