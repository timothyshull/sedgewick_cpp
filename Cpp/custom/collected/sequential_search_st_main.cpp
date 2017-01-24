int main(int argc, char *argv[]) {
    SequentialSearchST<String, Integer> st = new SequentialSearchST<String, Integer>();
    for (int i = 0; !StdIn.isEmpty(); i++) {
        String key = StdIn.readString();
        st.put(key, i);
    }
    for (String s : st.keys())
        StdOut.println(s + " " + st.get(s));
    return 0;
}