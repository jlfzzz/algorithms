from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class SegmentTree:
    def __init__(self, nums: List[int]) -> None:
        n = len(nums)
        self.tree = [0] * (2 << ((n - 1).bit_length()))
        self.build(nums, 1, 0, n - 1)

    def maintain(self, o):
        self.tree[o] = max(self.tree[o * 2], self.tree[o * 2 + 1])

    def build(self, nums, o, l, r):
        if l == r:
            self.tree[o] = nums[l]
            return
        m = (l + r) // 2
        self.build(nums, o * 2, l, m)
        self.build(nums, o * 2 + 1, m + 1, r)
        self.maintain(o)

    def query(self, o, L, R, target):
        return self.query_(o, 0, R, L, R, target)

    def query_(self, o, l, r, L, R, target):
        if self.tree[o] < target:
            return -1
        if r < L:
            return -1
        if l > R:
            return -1
        if l == r:
            if self.tree[o] >= target:
                return l
            else:
                return -1
        m = (l + r) // 2
        i = self.query_(o * 2, l, m, L, R, target)
        if i < 0:
            i = self.query_(o * 2 + 1, m + 1, r, L, R, target)
        self.maintain(o)
        return i


class Solution:
    def leftmostBuildingQueries(
        self, heights: List[int], queries: List[List[int]]
    ) -> List[int]:
        n = len(queries)
        ans = [-1] * n
        st = SegmentTree(heights)
        for k, (a, b) in enumerate(queries):
            if a == b:
                ans[k] = a
                continue

            h1, h2 = heights[a], heights[b]
            if a > b:
                a, b = b, a
                h1, h2 = h2, h1

            if h2 > h1:
                ans[k] = b
                continue

            h = max(h1, h2)
            j = st.query(1, b + 1, len(heights) - 1, h + 1)
            if j >= 0:
                ans[k] = j
        return ans
