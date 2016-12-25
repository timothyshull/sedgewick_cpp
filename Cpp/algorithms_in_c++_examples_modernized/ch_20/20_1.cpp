class EDGE {
public:
    EDGE(int, int, double);

    int v() const;

    int w() const;

    double wt() const;

    bool from(int) const;

    int other(int) const;
};

template<class Edge> class GRAPH {
public:
    GRAPH(int, bool);

    ~GRAPH();

    int V() const;

    int E() const;

    bool directed() const;

    int insert(Edge*);

    int remove(Edge*);

    Edge* edge(int, int);

    class adjIterator {
    public:
        adjIterator(const GRAPH&, int);

        Edge* beg();

        Edge* nxt();

        bool end();
    };
};

