from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        self._size = [1] * n
        self.cc = n

    def find(self, x: int) -> int:
        if self._fa[x] != x:
            self._fa[x] = self.find(self._fa[x])
        return self._fa[x]

    def is_same(self, x: int, y: int) -> bool:
        return self.find(x) == self.find(y)

    def merge(self, from_: int, to: int) -> bool:
        x, y = self.find(from_), self.find(to)
        if x == y:
            return False
        self._fa[x] = y
        self._size[y] += self._size[x]
        self.cc -= 1
        return True

    def get_size(self, x: int) -> int:
        return self._size[self.find(x)]


class Solution:
    def minCost(self, n: int, edges: List[List[int]], k: int) -> int:
        if k == n:
            return 0

        edges.sort(key=lambda e: e[2])
        u = UnionFind(n)
        for x, y, w in edges:
            u.merge(x, y)
            if u.cc <= k:
                return w
