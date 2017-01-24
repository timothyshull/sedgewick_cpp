int main(int argc, char *argv[]) {
    ResizingArrayStack<String> stack = new ResizingArrayStack<String>();
    while (!StdIn.isEmpty()) {
        String item = StdIn.readString();
        if (!item.equals("-")) stack.push(item);
        else if (!stack.isEmpty()) StdOut.print(stack.pop() + " ");
    }
    StdOut.println("(" + stack.size() + " left on stack)");
    return 0;
}