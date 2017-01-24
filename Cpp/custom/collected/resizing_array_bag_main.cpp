int main(int argc, char *argv[]) {
    ResizingArrayBag<std::string> bag = new ResizingArrayBag<std::string>();
    bag.add("Hello");
    bag.add("World");
    bag.add("how");
    bag.add("are");
    bag.add("you");

    for (String s : bag)
        Std_out::print_line(s);
    return 0;
}