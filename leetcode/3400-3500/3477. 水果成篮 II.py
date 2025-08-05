from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class SegmentTree:
    def __init__(self, n: int):
        self.n = n
        self.tree = [0] * (2 << n.bit_length())

    def update(self, o, l, r, i, val):
        if l == r:
            self.tree[o] = val
            return
        m = (l + r) // 2
        if i <= m:
            self.update(o * 2, l, m, i, val)
        else:
            self.update(o * 2 + 1, m + 1, r, i, val)
        self.tree[o] = max(self.tree[o * 2], self.tree[o * 2 + 1])

    def query(self, o, l, r, target):
        if self.tree[o] < target:
            return -1
        if l == r:
            return l
        m = (l + r) // 2
        res = self.query(o * 2, l, m, target)
        if res < 0:
            res = self.query(o * 2 + 1, m + 1, r, target)
        return res


class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        n = len(fruits)
        st = SegmentTree(n)
        for i, x in enumerate(baskets):
            st.update(1, 0, n - 1, i, x)
        ans = 0
        for i, x in enumerate(fruits):
            j = st.query(1, 0, n - 1, x)
            if j < 0:
                ans += 1
            else:
                st.update(1, 0, n - 1, j, 0)
        return ans
