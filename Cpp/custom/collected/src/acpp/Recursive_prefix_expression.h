#ifndef RECURSIVE_PREFIX_EXPRESSION_H
#define RECURSIVE_PREFIX_EXPRESSION_H

#include <string>

class Recursive_prefix_expression {
public:
    Recursive_prefix_expression(std::string& input);

    int eval();
private:
    std::string _input;
    int _index;
};

#endif // RECURSIVE_PREFIX_EXPRESSION_H
