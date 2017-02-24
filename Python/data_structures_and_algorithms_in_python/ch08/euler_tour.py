class EulerTour:
    def __init__(self, tree):
        self._tree = tree

    def tree(self):
        return self._tree

    def execute(self):
        if len(self._tree) > 0:
            return self._tour(self._tree.root(), 0, [])  # start the recursion

    def _tour(self, p, d, path):
        self._hook_previsit(p, d, path)  # "pre visit" p
        results = []
        path.append(0)  # add new index to end of path before recursion
        for c in self._tree.children(p):
            results.append(self._tour(c, d + 1, path))  # recur on child's subtree
            path[-1] += 1  # increment index
        path.pop()  # remove extraneous index from end of path
        answer = self._hook_postvisit(p, d, path, results)  # "post visit" p
        return answer

    def _hook_previsit(self, p, d, path):
        pass

    def _hook_postvisit(self, p, d, path, results):
        """Visit Position p, after the tour of its children.

        p        Position of current position being visited
        d        depth of p in the tree
        path     list of indices of children on path from root to p
        results  is a list of values returned by _hook_postvisit(c)
                for each child c of p.
        """
        pass


class PreorderPrintIndentedTour(EulerTour):
    def _hook_previsit(self, p, d, path):
        print(2 * d * ' ' + str(p.element()))


class PreorderPrintIndentedLabeledTour(EulerTour):
    def _hook_previsit(self, p, d, path):
        label = '.'.join(str(j + 1) for j in path)  # labels are one-indexed
        print(2 * d * ' ' + label, p.element())


class ParenthesizeTour(EulerTour):
    def _hook_previsit(self, p, d, path):
        if path and path[-1] > 0:  # p follows a sibling
            print(', ', end='')  # so preface with comma
        print(p.element(), end='')  # then print element
        if not self.tree().is_leaf(p):  # if p has children
            print(' (', end='')  # print opening parenthesis

    def _hook_postvisit(self, p, d, path, results):
        if not self.tree().is_leaf(p):  # if p has children
            print(')', end='')  # print closing parenthesis


class DiskSpaceTour(EulerTour):
    def _hook_postvisit(self, p, d, path, results):
        # we simply add space associated with p to that of its subtrees
        return p.element().space() + sum(results)


class BinaryEulerTour(EulerTour):
    def _tour(self, p, d, path):
        results = [None, None]  # will update with results of recursions
        self._hook_previsit(p, d, path)  # "pre visit" for p
        if self._tree.left(p) is not None:  # consider left child
            path.append(0)
            results[0] = self._tour(self._tree.left(p), d + 1, path)
            path.pop()
        self._hook_invisit(p, d, path)  # "in visit" for p
        if self._tree.right(p) is not None:  # consider right child
            path.append(1)
            results[1] = self._tour(self._tree.right(p), d + 1, path)
            path.pop()
        answer = self._hook_postvisit(p, d, path, results)  # "post visit" p
        return answer

    def _hook_invisit(self, p, d, path):
        pass


class BinaryLayout(BinaryEulerTour):
    def __init__(self, tree):
        super().__init__(tree)  # must call the parent constructor
        self._count = 0  # initialize count of processed nodes

    def _hook_invisit(self, p, d, path):
        p.element().setX(self._count)  # x-coordinate serialized by count
        p.element().setY(d)  # y-coordinate is depth
        self._count += 1  # advance count of processed nodes
