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


class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1)

    def update(self, i: int, val: int) -> None:
        i += 1
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i

    def pre(self, i: int) -> int:
        s = 0
        while i > 0:
            s += self.tree[i]
            i &= i - 1
        return s

    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r + 1) - self.pre(l)


class Solution:
    def countOfPeaks(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        ft = FenwickTree(n)
        for i in range(1, n - 1):
            x, l, r = nums[i], nums[i - 1], nums[i + 1]
            if l < x and x > r:
                ft.update(i, 1)

        ans = []
        for q in queries:
            if q[0] == 1:
                l, r = q[1], q[2]
                # 题目要求是[l+1,r-1]
                ans.append(ft.query(l + 1, r - 1))
            else:
                i, val = q[1], q[2]
                # 首尾两个肯定不是peak
                for j in range(max(i - 1, 1), min(i + 2, n - 1)):
                    if nums[j] > nums[j - 1] and nums[j] > nums[j + 1]:
                        ft.update(j, -1)
                nums[i] = val
                for j in range(max(i - 1, 1), min(i + 2, n - 1)):
                    if nums[j] > nums[j - 1] and nums[j] > nums[j + 1]:
                        ft.update(j, 1)
        return ans
