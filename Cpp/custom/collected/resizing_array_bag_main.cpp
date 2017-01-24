int main(int argc, char *argv[]) {
    ResizingArrayBag<String> bag = new ResizingArrayBag<String>();
    bag.add("Hello");
    bag.add("World");
    bag.add("how");
    bag.add("are");
    bag.add("you");

    for (String s : bag)
        StdOut.println(s);
    return 0;
}