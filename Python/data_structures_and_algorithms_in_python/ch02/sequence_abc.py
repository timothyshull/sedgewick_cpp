from abc import ABCMeta, abstractmethod  # need these definitions


class Sequence(metaclass=ABCMeta):
    @abstractmethod
    def __len__(self):

    @abstractmethod
    def __getitem__(self, j):

    def __contains__(self, val):
        for j in range(len(self)):
            if self[j] == val:  # found match
                return True
        return False

    def index(self, val):
        for j in range(len(self)):
            if self[j] == val:  # leftmost match
                return j
        raise ValueError('value not in sequence')  # never found a match

    def count(self, val):
        k = 0
        for j in range(len(self)):
            if self[j] == val:  # found a match
                k += 1
        return k
