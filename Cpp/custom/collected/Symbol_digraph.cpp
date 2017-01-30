#include "Symbol_digraph.h"
#include "In.h"

Symbol_digraph::Symbol_digraph(std::string& filename, const char delimiter)
        : _st{}
{
    In in{filename};
    while (in.hasNextLine()) {
        std::string line{in.read_line()};
        std::vector<std::string> a;
        utility::split_string(line, delimiter, a);
        for (int i{0}; i < a.size(); ++i) {
            if (!_st.contains(a[i])) {
                _st.put(a[i], _st.size());
            }
        }
    }

    _keys = std::vector<std::string>{static_cast<std::vector<std::string>::size_type>(_st.size())};
    for (auto name : _st.keys()) {
        _keys[_st.get(name)] = name;
    }

    _graph = Digraph{_st.size()};
    in = In{filename};
    while (in.hasNextLine()) {
        std::string line{in.read_line()};
        std::vector<std::string> a;
        utility::split_string(line, delimiter, a);
        int v = _st.get(a[0]);
        for (int i{1}; i < a.size(); ++i) {
            int w = _st.get(a[i]);
            _graph.add_edge(v, w);
        }
    }
}


