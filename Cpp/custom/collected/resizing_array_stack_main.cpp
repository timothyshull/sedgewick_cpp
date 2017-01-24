int main(int argc, char *argv[]) {
    ResizingArrayStack<std::string> stack = new ResizingArrayStack<std::string>();
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        if (!item.equals("-")) stack.push(item);
        else if (!stack.is_empty()) Std_out::print(stack.pop() + " ");
    }
    Std_out::print_line("(" + stack.size() + " left on stack)");
    return 0;
}