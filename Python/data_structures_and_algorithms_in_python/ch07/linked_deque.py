from .doubly_linked_base import _DoublyLinkedBase
from ..exceptions import Empty


class LinkedDeque(_DoublyLinkedBase):  # note the use of inheritance
    def first(self):
        if self.is_empty():
            raise Empty("Deque is empty")
        return self._header._next._element  # real item just after header

    def last(self):
        if self.is_empty():
            raise Empty("Deque is empty")
        return self._trailer._prev._element  # real item just before trailer

    def insert_first(self, e):
        self._insert_between(e, self._header, self._header._next)  # after header

    def insert_last(self, e):
        self._insert_between(e, self._trailer._prev, self._trailer)  # before trailer

    def delete_first(self):
        if self.is_empty():
            raise Empty("Deque is empty")
        return self._delete_node(self._header._next)  # use inherited method

    def delete_last(self):
        if self.is_empty():
            raise Empty("Deque is empty")
        return self._delete_node(self._trailer._prev)  # use inherited method
