#include "Symbol_graph.h"
#include "In.h"
#include "Std_out.h"
#include "utility.h"

Symbol_graph::Symbol_graph(std::string& filename, const char delimiter)
        : _st{}
{
    In<std::ifstream> in{filename};
    while (!in.is_empty()) {
        std::string line{in.read_line()};
        std::vector<std::string> a;
        utility::split_string(line, delimiter, a);
        for (auto i = 0; i < a.size(); ++i) {
            if (!_st.contains(a[i])) {
                _st.put(a[i], _st.size());
            }
        }
    }
    Std_out::print_line("Done reading " + filename);

    _keys = std::vector<std::string>{static_cast<std::vector<std::string>::size_type>(_st.size())};
    for (auto name : _st.keys()) {
        _keys[_st.get(name)] = name;
    }

    _graph = Graph{_st.size()};
    in = In{filename};
    while (!in.is_empty()) {
        std::string line{in.read_line()};
        std::vector<std::string> a;
        utility::split_string(line, delimiter, a);
        int v = _st.get(a[0]);
        for (auto i = 1; i < a.size(); ++i) {
            int w = _st.get(a[i]);
            _graph.add_edge(v, w);
        }
    }
}


