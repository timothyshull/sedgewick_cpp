// Program 22.2 - Flow-network edges
#ifndef FLOW_NETWORK_EDGE_H
#define FLOW_NETWORK_EDGE_H

class Flow_network_edge {
public:
    Flow_network_edge(int source, int destination, int capacity)
            : _p_source{source},
              _p_sink{destination},
              _p_capacity{capacity},
              _p_flow{0} {}

    inline int source() const noexcept { return _p_source; }

    inline int sink() const noexcept { return _p_sink; }

    inline int destination() const noexcept { return _p_sink; }

    inline int capacity() const noexcept { return _p_capacity; }

    inline int flow() const noexcept { return _p_flow; }

    inline bool from(int v) const noexcept { return _p_source == v; }

    inline int other(int v) const noexcept { return from(v) ? _p_sink : _p_source; }

    inline int cap_r_to(int v) const noexcept { return from(v) ? _p_flow : _p_capacity - _p_flow; }

    inline void add_flow_r_to(int v, int d) { _p_flow += from(v) ? -d : d; }

private:
    int _p_source;
    int _p_sink;
    int _p_capacity;
    int _p_flow;
};

#endif // FLOW_NETWORK_EDGE_H
