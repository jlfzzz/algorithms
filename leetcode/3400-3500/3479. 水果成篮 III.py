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
        self.n = len(nums)
        self.tree = [0] * (2 << ((self.n - 1).bit_length()))
        self.build(nums, 1, 0, self.n - 1)

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

    def query(self, o, l, r, target):
        if self.tree[o] < target:
            return -1
        if l == r:
            if self.tree[o] >= target:
                self.tree[o] = -1
                return 1
            else:
                return -1

        m = (l + r) // 2
        t = self.query(o * 2, l, m, target)
        if t < 0:
            t = self.query(o * 2 + 1, m + 1, r, target)
        self.maintain(o)
        return t


class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        st = SegmentTree(baskets)
        ans = 0
        for x in fruits:
            i = st.query(1, 0, len(baskets) - 1, x)
            if i < 0:
                ans += 1
        return ans


class SegmentTree:
    def __init__(self, nums: List[int]):
        self.n = len(nums)
        self.tree = [-1] * (2 << ((self.n - 1).bit_length()))
        self.build(nums, 1, 0, self.n - 1)

    def build(self, nums, o, l, r):
        if l == r:
            self.tree[o] = nums[l]
            return
        m = (l + r) // 2
        self.build(nums, o * 2, l, m)
        self.build(nums, o * 2 + 1, m + 1, r)
        self.maintain(o)

    def maintain(self, o):
        self.tree[o] = max(self.tree[o * 2], self.tree[o * 2 + 1])

    def query(self, o, l, r, target):
        if self.tree[o] < target:
            return -1

        if l == r:
            self.tree[o] = -1
            return 0
        m = (l + r) // 2
        i = self.query(o * 2, l, m, target)
        if i < 0:
            i = self.query(o * 2 + 1, m + 1, r, target)
        self.maintain(o)
        return i


class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        st = SegmentTree(baskets)
        ans = 0
        n = len(baskets)
        for x in fruits:
            i = st.query(1, 0, n - 1, x)
            if i < 0:
                ans += 1
        return ans
