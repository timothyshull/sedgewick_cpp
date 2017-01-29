#include "Huffman.h"
#include "Binary_std_in.h"
#include "utility.h"
#include "Binary_std_out.h"
#include "Min_pq.h"

Huffman::Node::Node(char ch, int freq, Huffman::Raw_node_pointer left, Huffman::Raw_node_pointer right)
        : _ch{ch},
          _freq{freq},
          _left{left},
          _right{right} {}

bool Huffman::Node::operator<(Huffman::Node& rhs)
{
    return this->_freq < rhs._freq;
}

bool Huffman::Node::_is_leaf()
{
    utility::alg_assert(((_left == nullptr) && (_right == nullptr)) || ((_left != nullptr) && (_right != nullptr)), "Huffman Node _is_leaf check failed");
    return _left == nullptr && _right == nullptr;
}

void Huffman::compress()
{
    std::string s{Binary_std_in::read_string()};
    std::vector<char> input{utility::str_to_char_vector(s)};

    std::vector<int> freq;
    freq.reserve(static_cast<std::vector<int>::size_type>(radix));
    for (int i{0}; i < input.size(); ++i) {
        freq[input[i]]++;
    }

    Raw_node_pointer root = build_trie(freq);

    std::vector<std::string> st;
    st.reserve(static_cast<std::vector<std::string>::size_type>(radix));
    build_code(st, root, "");

    write_trie(root);

    Binary_std_out::write(input.size());

    for (int i{0}; i < input.size(); ++i) {
        std::string code = st[input[i]];
        for (int j{0}; j < code.size(); ++j) {
            if (code[j] == '0') {
                Binary_std_out::write(false);
            } else if (code[j] == '1') {
                Binary_std_out::write(true);
            } else { throw utility::Illegal_argument_exception{"Illegal state"}; }
        }
    }
    Binary_std_out::close();
}

Huffman::Raw_node_pointer Huffman::build_trie(std::vector<int>& freq)
{
    Min_pq<Raw_node_pointer> pq;
    for (char i{0}; i < radix; ++i) {
        if (freq[i] > 0) {
            Raw_node_pointer n{new Node(i, freq[i], nullptr, nullptr)};
            pq.insert(n);
        }
    }

    if (pq.size() == 1) {
        if (freq['\0'] == 0) {
            Raw_node_pointer n{new Node('\0', 0, nullptr, nullptr)};
            pq.insert(n);
        } else {
            Raw_node_pointer n{new Node('\1', 0, nullptr, nullptr)};
            pq.insert(n);
        }
    }

    while (pq.size() > 1) {
        Raw_node_pointer left = pq.delete_min();
        Raw_node_pointer right = pq.delete_min();
        Raw_node_pointer parent{new Node('\0', left->_freq + right->_freq, left, right)};
        pq.insert(parent);
    }
    return pq.delete_min();
}

void Huffman::write_trie(Huffman::Raw_node_pointer x)
{
    if (x->_is_leaf()) {
        Binary_std_out::write(true);
        Binary_std_out::write(x->_ch, 8);
        return;
    }
    Binary_std_out::write(false);
    write_trie(x->_left);
    write_trie(x->_right);
}

void Huffman::build_code(std::vector<std::string>& st, Huffman::Raw_node_pointer x, std::string& s)
{
    if (!x->_is_leaf()) {
        build_code(st, x->_left, s + '0');
        build_code(st, x->_right, s + '1');
    } else {
        st[x->_ch] = s;
    }
}

void Huffman::build_code(std::vector<std::string>& st, Huffman::Raw_node_pointer x, std::string&& s)
{
    if (!x->_is_leaf()) {
        build_code(st, x->_left, s + '0');
        build_code(st, x->_right, s + '1');
    } else {
        st[x->_ch] = s;
    }
}

void ::Huffman::expand()
{
    Raw_node_pointer root = read_trie();

    int length{Binary_std_in::read_int()};

    for (int i{0}; i < length; ++i) {
        Raw_node_pointer x = root;
        while (!x->_is_leaf()) {
            bool bit = Binary_std_in::read_boolean();
            if (bit) { x = x->_right; }
            else { x = x->_left; }
        }
        Binary_std_out::write(x->_ch, 8);
    }
    Binary_std_out::close();
}

Huffman::Raw_node_pointer Huffman::read_trie()
{
    bool is_leaf{Binary_std_in::read_boolean()};
    if (is_leaf) {
        return new Node(Binary_std_in::read_char(), -1, nullptr, nullptr);
    } else {
        return new Node('\0', -1, read_trie(), read_trie());
    }
}
