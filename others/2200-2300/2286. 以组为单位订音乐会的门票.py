import sys
import math
import bisect
import heapq
import collections
import functools
import itertools
import threading
from typing import List


class BookMyShow:

    def __init__(self, n: int, m: int):
        self.n = n
        self.m = m
        self.tree_sum = [0] * 4 * n
        self.mn = [0] * 4 * n

    def update(self, o: int, l: int, r: int, target: int, val: int) -> None:
        if l == r:
            self.tree_sum[o] += val
            self.mn[o] += val
            return

        mid = (l + r) // 2
        if target <= mid:
            self.update(o * 2, l, mid, target, val)
        else:
            self.update(o * 2 + 1, mid + 1, r, target, val)

        self.mn[o] = min(self.mn[o * 2], self.mn[o * 2 + 1])
        self.tree_sum[o] = self.tree_sum[o * 2] + self.tree_sum[o * 2 + 1]

    def query_sum(self, o: int, l: int, r: int, L: int, R: int) -> int:
        if L <= l and R >= r:
            return self.tree_sum[o]

        mid = (l + r) // 2
        res = 0
        if L <= mid:
            res += self.query_sum(o * 2, l, mid, L, R)
        if R > mid:
            res += self.query_sum(o * 2 + 1, mid + 1, r, L, R)
        return res

    def find_first(self, o: int, l: int, r: int, max_r: int, val: int):
        if self.mn[o] > val:
            return -1

        if l == r:
            return l

        mid = (l + r) // 2
        if self.mn[o * 2] <= val:
            return self.find_first(o * 2, l, mid, max_r, val)
        if max_r > mid:
            return self.find_first(o * 2 + 1, mid + 1, r, max_r, val)
        return -1

    def gather(self, k: int, maxRow: int) -> List[int]:
        row = self.find_first(1, 0, self.n - 1, maxRow, self.m - k)
        if row < 0:
            return []

        prev_cnt = self.query_sum(1, 0, self.n - 1, row, row)
        self.update(1, 0, self.n - 1, row, k)
        return [row, prev_cnt]

    def scatter(self, k: int, maxRow: int) -> bool:
        s = self.query_sum(1, 0, self.n - 1, 0, maxRow)
        if s > self.m * (maxRow + 1) - k:
            return False

        idx = self.find_first(1, 0, self.n - 1, maxRow, self.m - 1)
        while k:
            left = min(self.m - self.query_sum(1, 0, self.n - 1, idx, idx), k)
            self.update(1, 0, self.n - 1, idx, left)
            k -= left
            idx += 1
        return True


# Your BookMyShow object will be instantiated and called as such:
# obj = BookMyShow(n, m)
# param_1 = obj.gather(k, maxRow)
# param_2 = obj.scatter(k, maxRow)
