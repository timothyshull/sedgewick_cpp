int main(int argc, char *argv[]) {
    int m = Integer.parseInt(args[0]);
    MinPQ<Transaction> pq = new MinPQ<Transaction>(m + 1);

    while (StdIn.hasNextLine()) {
        // Create an entry from the next line and put on the PQ.
        String line = StdIn.readLine();
        Transaction transaction = new Transaction(line);
        pq.insert(transaction);

        // remove minimum if m+1 entries on the PQ
        if (pq.size() > m)
            pq.delMin();
    }   // top m entries are on the PQ

    // print entries on PQ in reverse order
    Stack<Transaction> stack = new Stack<Transaction>();
    for (Transaction transaction : pq)
        stack.push(transaction);
    for (Transaction transaction : stack)
        StdOut.println(transaction);
    return 0;
}