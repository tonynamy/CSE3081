import enum
import math
import random
from numbers import Number
import typing


class Heap:
    is_max = True
    _heap = [-1]

    class HeapIsEmptyException(Exception):
        pass

    class UnsupportedAdjustDirectionException(Exception):
        pass

    class AdjustDirection(enum.Enum):
        UP = enum.auto()
        DOWN = enum.auto

    @property
    def size(self) -> int:
        return len(self._heap) - 1

    @property
    def is_empty(self) -> bool:
        return self.size == 0

    @property
    def heap(self) -> typing.List[Number]:
        return self._heap[1:]

    @property
    def _end_value(self) -> Number:
        return -math.inf if self.is_max else math.inf

    def _compare(self, a: Number, b: Number) -> bool:
        return a > b if self.is_max else a < b

    def _compare_idx(self, a: int, b: int) -> bool:
        return self._compare(self._heap[a], self._heap[b])

    def _swap(self, a, b):
        self._heap[a], self._heap[b] = self._heap[b], self._heap[a]

    def _adjust_up(self, idx: int):
        if idx <= 1:
            return

        if self._compare_idx(int(idx / 2), idx):
            return

        self._swap(idx, int(idx / 2))

        self._adjust_up(int(idx / 2))

    def _adjust_down(self, idx: int):
        if idx >= self.size:
            return

        to_idx: int = idx

        if idx * 2 <= self.size and self._compare_idx(idx * 2, to_idx):
            to_idx = idx * 2

        if idx * 2 + 1 <= self.size and self._compare_idx(idx * 2 + 1, to_idx):
            to_idx = idx * 2 + 1

        if idx == to_idx:
            return

        self._swap(idx, to_idx)

        self._adjust_down(to_idx)

    def _adjust(self, idx: int, *, direction: AdjustDirection):
        if direction == Heap.AdjustDirection.UP:
            self._adjust_up(idx)
        elif direction == Heap.AdjustDirection.DOWN:
            self._adjust_down(idx)
        else:
            raise Heap.UnsupportedAdjustDirectionException()

    def push(self, a: Number):
        self._heap.append(a)
        self._adjust(self.size, direction=Heap.AdjustDirection.UP)

    def pop(self) -> Number:

        if self.is_empty:
            raise Heap.HeapIsEmptyException()

        self._swap(1, self.size)

        top = self._heap.pop()

        if not self.is_empty:
            self._adjust(1, direction=Heap.AdjustDirection.DOWN)

        return top


if __name__ == "__main__":

    heap = Heap()

    SIZE = 100
    RANGE = 100

    for _ in range(SIZE):
        heap.push(random.randint(-RANGE, RANGE))

    for _ in range(SIZE):
        print(heap.pop())
