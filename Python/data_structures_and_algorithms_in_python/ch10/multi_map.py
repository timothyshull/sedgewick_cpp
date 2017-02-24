class MultiMap:
    _MapType = dict  # Map type; can be redefined by subclass

    def __init__(self):
        self._map = self._MapType()  # create map instance for storage
        self._n = 0

    def __len__(self):
        return self._n

    def __iter__(self):
        for k, secondary in self._map.items():
            for v in secondary:
                yield (k, v)

    def add(self, k, v):
        container = self._map.setdefault(k, [])  # create empty list, if needed
        container.append(v)
        self._n += 1

    def pop(self, k):
        secondary = self._map[k]  # may raise KeyError
        v = secondary.pop()
        if len(secondary) == 0:
            del self._map[k]  # no pairs left
        self._n -= 1
        return k, v

    def find(self, k):
        secondary = self._map[k]  # may raise KeyError
        return k, secondary[0]

    def find_all(self, k):
        secondary = self._map.get(k, [])  # empty list, by default
        for v in secondary:
            yield (k, v)
