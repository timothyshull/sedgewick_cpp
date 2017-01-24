int main(int argc, char *argv[]) {
    ResizingArrayQueue<String> queue = new ResizingArrayQueue<String>();
    while (!StdIn.isEmpty()) {
        String item = StdIn.readString();
        if (!item.equals("-")) queue.enqueue(item);
        else if (!queue.isEmpty()) StdOut.print(queue.dequeue() + " ");
    }
    StdOut.println("(" + queue.size() + " left on queue)");
    return 0;
}