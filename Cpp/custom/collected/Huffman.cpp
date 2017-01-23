#include "Huffman.h"

bool Huffman::Node::operator<(Huffman::Node& rhs)
{
    return this->freq < rhs.freq;
}

bool Huffman::Node::isLeaf()
{
    assert((left == null) && (right == null)) || ((left != null) && (right != null));
    return (left == null) && (right == null);
}

void ::Huffman::compress()
{
    String s = BinaryStdIn.readString();
    char
    []
    input = s.toCharArray();

    // tabulate frequency counts
    int
    []
    freq = new int[R];
    for (int i = 0; i < input.length; i++) {
        freq[input[i]]++;
    }

    // build Huffman trie
    Node root = buildTrie(freq);

    // build code table
    String[]
    st = new String[R];
    buildCode(st, root, "");

    // print trie for decoder
    writeTrie(root);

    // print number of bytes in original uncompressed message
    BinaryStdOut.write(input.length);

    // use Huffman code to encode input
    for (int i = 0; i < input.length; i++) {
        String code = st[input[i]];
        for (int j = 0; j < code.length(); j++) {
            if (code.charAt(j) == '0') {
                BinaryStdOut.write(false);
            } else if (code.charAt(j) == '1') {
                BinaryStdOut.write(true);
            } else { throw new IllegalStateException("Illegal state"); }
        }
    }

    // close output stream
    BinaryStdOut.close();
}

Huffman::Raw_node_pointer Huffman::buildTrie(std::vector<int>& freq)
{
    MinPQ <Node> pq = new MinPQ<Node>();
    for (char i = 0; i < R; i++) {
        if (freq[i] > 0) {
            pq.insert(new Node(i, freq[i], null, null));
        }
    }

    // special case in case there is only one character with a nonzero frequency
    if (pq.size() == 1) {
        if (freq['\0'] == 0) { pq.insert(new Node('\0', 0, null, null)); }
        else { pq.insert(new Node('\1', 0, null, null)); }
    }

    // merge two smallest trees
    while (pq.size() > 1) {
        Node left = pq.delMin();
        Node right = pq.delMin();
        Node parent = new Node('\0', left.freq + right.freq, left, right);
        pq.insert(parent);
    }
    return pq.delMin();
}

void ::Huffman::writeTrie(Huffman::Raw_node_pointer x)
{
    if (x.isLeaf()) {
        BinaryStdOut.write(true);
        BinaryStdOut.write(x.ch, 8);
        return;
    }
    BinaryStdOut.write(false);
    writeTrie(x.left);
    writeTrie(x.right);
}

void ::Huffman::buildCode(std::vector<std::string>& st, Huffman::Raw_node_pointer x, std::string& s)
{
    if (!x.isLeaf()) {
        buildCode(st, x.left, s + '0');
        buildCode(st, x.right, s + '1');
    } else {
        st[x.ch] = s;
    }
}

void ::Huffman::expand()
{
    Node root = readTrie();

    // number of bytes to write
    int length = BinaryStdIn.readInt();

    // decode using the Huffman trie
    for (int i = 0; i < length; i++) {
        Node x = root;
        while (!x.isLeaf()) {
            boolean bit = BinaryStdIn.readBoolean();
            if (bit) { x = x.right; }
            else { x = x.left; }
        }
        BinaryStdOut.write(x.ch, 8);
    }
    BinaryStdOut.close();
}

Huffman::Raw_node_pointer Huffman::readTrie()
{
    boolean isLeaf = BinaryStdIn.readBoolean();
    if (isLeaf) {
        return new Node(BinaryStdIn.readChar(), -1, null, null);
    } else {
        return new Node('\0', -1, readTrie(), readTrie());
    }
}
