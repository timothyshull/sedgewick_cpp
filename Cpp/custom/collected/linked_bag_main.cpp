int main(int argc, char *argv[]) {
    LinkedBag<std::string> bag = new LinkedBag<std::string>();
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        bag.add(item);
    }

    Std_out::print_line("size of bag = " + bag.size());
    for (String s : bag) {
        Std_out::print_line(s);
    }
    return 0;
}