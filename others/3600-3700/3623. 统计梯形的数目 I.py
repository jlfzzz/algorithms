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
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def countTrapezoids(self, points: List[List[int]]) -> int:
        MOD = 1_000_000_007
        cnt = Counter(p[1] for p in points)  # 统计每一行（水平线）有多少个点
        ans = s = 0
        for c in cnt.values():
            k = c * (c - 1) // 2
            ans += s * k
            s += k
        return ans % MOD
