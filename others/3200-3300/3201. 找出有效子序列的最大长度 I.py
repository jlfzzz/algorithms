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


class Solution:
    def maximumLength(self, nums: List[int]) -> int:
        f0, f1, f2, f3 = 0, 0, 0, 0
        for x in nums:
            if x % 2:
                f1 += 1
                f3 = Max(f3, f2 + 1)
            else:
                f0 += 1
                f2 = Max(f2, f3 + 1)
        return max(f0, f1, f2, f3)
