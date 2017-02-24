from .priority_queue_base import PriorityQueueBase
from ..ch07.positional_list import PositionalList
from ..exceptions import Empty


class UnsortedPriorityQueue(PriorityQueueBase):  # base class defines _Item


    # ----------------------------- nonpublic behavior -----------------------------
    def _find_min(self):
        if self.is_empty():  # is_empty inherited from base class
            raise Empty('Priority queue is empty')
        small = self._data.first()
        walk = self._data.after(small)
        while walk is not None:
            if walk.element() < small.element():
                small = walk
            walk = self._data.after(walk)
        return small

    # ------------------------------ public behaviors ------------------------------
    def __init__(self):
        self._data = PositionalList()

    def __len__(self):
        return len(self._data)

    def add(self, key, value):
        self._data.add_last(self._Item(key, value))

    def min(self):
        p = self._find_min()
        item = p.element()
        return (item._key, item._value)

    def remove_min(self):
        p = self._find_min()
        item = self._data.delete(p)
        return (item._key, item._value)
