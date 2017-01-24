int main(int argc, char *argv[]) {
    SparseVector a = new SparseVector(10);
    SparseVector b = new SparseVector(10);
    a.put(3, 0.50);
    a.put(9, 0.75);
    a.put(6, 0.11);
    a.put(6, 0.00);
    b.put(3, 0.60);
    b.put(4, 0.90);
    StdOut.println("a = " + a);
    StdOut.println("b = " + b);
    StdOut.println("a dot b = " + a.dot(b));
    StdOut.println("a + b   = " + a.plus(b));
    return 0;
}