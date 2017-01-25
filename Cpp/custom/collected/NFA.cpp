#include "NFA.h"

NFA::NFA(std::string& regexp)
{
    this.regexp = regexp;
    m = regexp.length();
    Stack<Integer> ops = new Stack<Integer>();
    graph = new Digraph(m + 1);
    for (int i = 0; i < m; ++i) {
        int lp = i;
        if (regexp.charAt(i) == '(' || regexp.charAt(i) == '|')
            ops.push(i);
        else if (regexp.charAt(i) == ')') {
            int or = ops.pop();

            // 2-way or operator
            if (regexp.charAt(or) == '|') {
                lp = ops.pop();
                graph.add_edge(lp, or + 1);
                graph.add_edge(or, i);
            } else if (regexp.charAt(or) == '(')
            lp = or;
            else assert false;
        }

        // closure operator (uses 1-character lookahead)
        if (i < m - 1 && regexp.charAt(i + 1) == '*') {
            graph.add_edge(lp, i + 1);
            graph.add_edge(i + 1, lp);
        }
        if (regexp.charAt(i) == '(' || regexp.charAt(i) == '*' || regexp.charAt(i) == ')')
            graph.add_edge(i, i + 1);
    }
    if (ops.size() != 0)
        throw utility::Illegal_argument_exception("Invalid regular expression");
}

bool NFA::recognizes(std::string& txt)
{
    DirectedDFS dfs = new DirectedDFS(graph, 0);
    Bag<Integer> pc = new Bag<Integer>();
    for (int v = 0; v < graph.num_vertices(); ++v)
        if (dfs.marked(v)) pc.add(v);

    // Compute possible NFA states for txt[i+1]
    for (int i = 0; i < txt.length(); ++i) {
        if (txt.charAt(i) == '*' || txt.charAt(i) == '|' || txt.charAt(i) == '(' || txt.charAt(i) == ')')
            throw utility::Illegal_argument_exception("text contains the metacharacter '" + txt.charAt(i) + "'");

        Bag<Integer> match = new Bag<Integer>();
        for (int v : pc) {
            if (v == m) continue;
            if ((regexp.charAt(v) == txt.charAt(i)) || regexp.charAt(v) == '.')
                match.add(v + 1);
        }
        dfs = new DirectedDFS(graph, match);
        pc = new Bag<Integer>();
        for (int v = 0; v < graph.num_vertices(); ++v)
            if (dfs.marked(v)) pc.add(v);

        // optimization if no states reachable
        if (pc.size() == 0) return false;
    }

    // check for accept state
    for (int v : pc)
        if (v == m) return true;
    return false;
}
