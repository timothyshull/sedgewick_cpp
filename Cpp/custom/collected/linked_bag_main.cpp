int main(int argc, char *argv[]) {
    LinkedBag<String> bag = new LinkedBag<String>();
    while (!StdIn.isEmpty()) {
        String item = StdIn.readString();
        bag.add(item);
    }

    StdOut.println("size of bag = " + bag.size());
    for (String s : bag) {
        StdOut.println(s);
    }
    return 0;
}