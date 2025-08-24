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
    def maxWalls(self, robots: List[int], distance: List[int], walls: List[int]) -> int:
        n, m = len(robots), len(walls)
        pairs = list(zip(robots, distance))
        pairs.sort()
        walls.sort()

        def calc(L, R):
            if L > R:
                return 0
            l = bisect_left(walls, L)
            r = bisect_right(walls, R)
            return r - l

        left_cnt = [0] * n
        right_cnt = [0] * n
        left_segs = [0] * n
        right_segs = [0] * n

        for i, (x, d) in enumerate(pairs):
            L = max(x - d, pairs[i - 1][0] + 1 if i > 0 else -1)
            R = x
            left_segs[i] = (L, R)
            left_cnt[i] = calc(L, R)

            L2 = x
            R2 = min(x + d, pairs[i + 1][0] - 1 if i < n - 1 else inf)
            right_segs[i] = (L2, R2)
            right_cnt[i] = calc(L2, R2)

        dup = [0] * n
        for i in range(1, n):
            l = max(right_segs[i - 1][0], left_segs[i][0])
            r = min(right_segs[i - 1][1], left_segs[i][1])
            dup[i] = calc(l, r)

        f1 = left_cnt[0]
        f2 = right_cnt[0]
        for i in range(1, n):
            f3 = max(f1 + left_cnt[i], f2 + left_cnt[i] - dup[i])
            f4 = max(f1, f2) + right_cnt[i]
            f1, f2 = f3, f4

        return max(f1, f2)
