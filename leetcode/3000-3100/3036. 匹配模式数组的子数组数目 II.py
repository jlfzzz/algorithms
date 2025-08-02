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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def countMatchingSubarrays(self, nums: List[int], pattern: List[int]) -> int:
        n, m = len(nums), len(pattern)

        nxt = [0] * m
        i = 1
        length = 0
        while i < m:
            while length > 0 and pattern[i] != pattern[length]:
                length = nxt[length - 1]
            if pattern[i] == pattern[length]:
                length += 1
            nxt[i] = length
            i += 1

        ans = 0
        i = 1
        j = 0

        def f(d):
            if d < 0:
                return -1
            elif d == 0:
                return 0
            else:
                return 1

        while i < n:
            while j > 0 and f(nums[i] - nums[i - 1]) != pattern[j]:
                j = nxt[j - 1]

            if f(nums[i] - nums[i - 1]) == pattern[j]:
                j += 1
            if j == m:
                ans += 1
                j = nxt[j - 1]
            i += 1
        return ans
