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


class Solution:
    def minimumArea(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        l, r, t, d = inf, 0, inf, 0
        ans = 0
        for i, x in enumerate(grid):
            for j, y in enumerate(x):
                if y:
                    l = min(l, j)
                    r = max(r, j)
                    t = min(t, i)
                    d = max(d, i)
        ans = (r - l + 1) * (d - t + 1)
        return ans
