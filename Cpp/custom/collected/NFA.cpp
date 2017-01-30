#include "NFA.h"
#include "Stack.h"
#include "Directed_dfs.h"

NFA::NFA(std::string& regexp)
        : _regexp{regexp},
          _size{static_cast<int>(regexp.length())},
          _graph{_size + 1}
{
    Stack<int> ops;
    for (int i{0}; i < _size; ++i) {
        int lp{i};
        if (regexp[i] == '(' || regexp[i] == '|') {
            ops.push(i);
        } else if (regexp[i] == ')') {
            int op_or{ops.pop()};
            if (regexp[op_or] == '|') {
                lp = ops.pop();
                _graph.add_edge(lp, op_or + 1);
                _graph.add_edge(op_or, i);
            } else if (regexp[op_or] == '(') {
                lp = op_or;
            } else { utility::alg_assert(false, "Bad operator"); }
        }

        if (i < _size - 1 && regexp[i + 1] == '*') {
            _graph.add_edge(lp, i + 1);
            _graph.add_edge(i + 1, lp);
        }
        if (regexp[i] == '(' || regexp[i] == '*' || regexp[i] == ')') {
            _graph.add_edge(i, i + 1);
        }
    }
    if (ops.size() != 0) {
        throw utility::Illegal_argument_exception("Invalid regular expression");
    }
}

bool NFA::recognizes(std::string& txt)
{
    Directed_dfs dfs{_graph, 0};
    std::vector<int> pc;
    for (int v{0}; v < _graph.num_vertices(); ++v) {
        if (dfs.marked(v)) { pc.emplace_back(v); }
    }

    for (int i{0}; i < txt.length(); ++i) {
        if (txt[i] == '*' || txt[i] == '|' || txt[i] == '(' || txt[i] == ')') {
            throw utility::Illegal_argument_exception("text contains the metacharacter '" + std::to_string(txt[i]) + "'");
        }

        std::vector<int> match;
        for (auto v : pc) {
            if (v == _size) { continue; }
            if ((_regexp[v] == txt[i]) || _regexp[v] == '.') {
                auto tmp = v + 1;
                match.emplace_back(tmp);
            }
        }
        dfs = Directed_dfs{_graph, match};
        pc.clear();
        for (int v{0}; v < _graph.num_vertices(); ++v) {
            if (dfs.marked(v)) { pc.emplace_back(v); }
        }

        if (pc.size() == 0) { return false; }
    }

    for (int v : pc) {
        if (v == _size) { return true; }
    }
    return false;
}
