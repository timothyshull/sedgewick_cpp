int main(int argc, char *argv[]) {
    ResizingArrayQueue<std::string> queue = new ResizingArrayQueue<std::string>();
    while (!Std_in::is_empty()) {
        std::string item = Std_in::read_string();
        if (!item.equals("-")) queue.enqueue(item);
        else if (!queue.is_empty()) Std_out::print(queue.dequeue() + " ");
    }
    Std_out::print_line("(" + queue.size() + " left on queue)");
    return 0;
}