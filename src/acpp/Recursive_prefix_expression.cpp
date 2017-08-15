#include "Recursive_prefix_expression.h"

Recursive_prefix_expression::Recursive_prefix_expression(std::string& input)
        : _input{input},
          _index{0} {}

int Recursive_prefix_expression::eval()
{
    auto x = 0;

    while (_index < _input.size() && _input[_index] == ' ') { ++_index; }

    if (_index == _input.size()) { return x; }

    if (_input[_index] == '+') {
        ++_index;
        return eval() + eval();
    }

    if (_input[_index] == '*') {
        ++_index;
        return eval() * eval();
    }

    while (_index < _input.size() && (_input[_index] >= '0') && (_input[_index] <= '9')) {
        x = 10 * x + (_input[_index++] - '0');
    }

    return x;
}
