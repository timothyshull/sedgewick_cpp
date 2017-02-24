class SequenceIterator:
    def __init__(self, sequence):
        self._seq = sequence  # keep a reference to the underlying data
        self._k = -1  # will increment to 0 on first call to next

    def __next__(self):
        self._k += 1  # advance to next index
        if self._k < len(self._seq):
            return (self._seq[self._k])  # return the data element
        else:
            raise StopIteration()  # there are no more elements

    def __iter__(self):
        return self
