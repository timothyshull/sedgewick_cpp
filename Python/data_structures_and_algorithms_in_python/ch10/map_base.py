from collections import MutableMapping


class MapBase(MutableMapping):
    # ------------------------------- nested _Item class -------------------------------
    class _Item:
        __slots__ = '_key', '_value'

        def __init__(self, k, v):
            self._key = k
            self._value = v

        def __eq__(self, other):
            return self._key == other._key  # compare items based on their keys

        def __ne__(self, other):
            return not (self == other)  # opposite of __eq__

        def __lt__(self, other):
            return self._key < other._key  # compare items based on their keys

    def __contains__(self, x):  # abstract method -> Container
        return False

    def __iter__(self):  # abstract method -> Iterable
        while False:
            yield None

    def __len__(self):  # abstract method -> Sized
        return 0

    def __getitem__(self, key):  # abstract method -> Mapping
        raise KeyError

    def __setitem__(self, key, value):  # abstract method -> MutableMapping
        raise KeyError

    def __delitem__(self, key):  # abstract method -> MutableMapping
        raise KeyError
