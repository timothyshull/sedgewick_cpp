#include "Huffman.h"
#include "Binary_std_in.h"

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
    std::string s = Binary_std_in::read_string();
    std::vector<char> input{utility::str_to_char_vector(s)};

    std::vector<int> freq = new int[R];
    for (int i{0}; i < input.length; ++i) {
        freq[input[i]]++;
    }

    // build Huffman trie
    Node root = buildTrie(freq);

    // build code table
    std::vector<std::string>
    st = new String[R];
    buildCode(st, root, "");

    // print trie for decoder
    writeTrie(root);

    // print number of bytes in original uncompressed message
    Binary_std_out::write(input.length);

    // use Huffman code to encode input
    for (int i{0}; i < input.length; ++i) {
        std::string code = st[input[i]];
        for (int j{0}; j < code.length(); ++j) {
            if (code.charAt(j) == '0') {
                Binary_std_out::write(false);
            } else if (code.charAt(j) == '1') {
                Binary_std_out::write(true);
            } else { throw new IllegalStateException("Illegal state"); }
        }
    }

    // close output stream
    Binary_std_out::close();
}

Huffman::Raw_node_pointer Huffman::buildTrie(std::vector<int>& freq)
{
    MinPQ <Node> pq = new MinPQ<Node>();
    for (char i{0}; i < R; ++i) {
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
        Binary_std_out::write(true);
        Binary_std_out::write(x.ch, 8);
        return;
    }
    Binary_std_out::write(false);
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
    int length = Binary_std_in::read_int();

    // decode using the Huffman trie
    for (int i{0}; i < length; ++i) {
        Node x = root;
        while (!x.isLeaf()) {
            bool bit = Binary_std_in::read_boolean();
            if (bit) { x = x.right; }
            else { x = x.left; }
        }
        Binary_std_out::write(x.ch, 8);
    }
    Binary_std_out::close();
}

Huffman::Raw_node_pointer Huffman::readTrie()
{
    bool isLeaf = Binary_std_in::read_boolean();
    if (isLeaf) {
        return new Node(Binary_std_in::read_char(), -1, null, null);
    } else {
        return new Node('\0', -1, readTrie(), readTrie());
    }
}
