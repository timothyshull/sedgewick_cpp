from copy import deepcopy


def floyd_warshall(g):
    closure_copy = deepcopy(g)  # imported from copy module
    vertices = list(closure_copy.vertices())  # make indexable list
    n = len(vertices)
    for k in range(n):
        for i in range(n):
            # verify that edge (i,k) exists in the partial closure
            if i != k and closure_copy.get_edge(vertices[i], vertices[k]) is not None:
                for j in range(n):
                    # verify that edge (k,j) exists in the partial closure
                    if i != j != k and closure_copy.get_edge(vertices[k], vertices[j]) is not None:
                        # if (i,j) not yet included, add it to the closure
                        if closure_copy.get_edge(vertices[i], vertices[j]) is None:
                            closure_copy.insert_edge(vertices[i], vertices[j])
    return closure_copy


if __name__ == '__main__':
    from .graph_examples import figure_14_11 as example

    g = example()
    print("Number of vertices is", g.vertex_count())
    print("Number of edges is", g.edge_count())
    closure = floyd_warshall(g)
    print("Number of edges in closure is", closure.edge_count())
