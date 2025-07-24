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
    def mincostTickets(self, days: List[int], costs: List[int]) -> int:
        n = len(days)

        @cache
        def dfs(i: int) -> int:
            if i >= n:
                return 0
            res = dfs(i + 1) + min(costs)
            j = i + 1
            while j < n and days[j] - days[i] < 7:
                j += 1
            res = Min(res, dfs(j) + costs[1])

            while j < n and days[j] - days[i] < 30:
                j += 1
            res = Min(res, dfs(j) + costs[2])
            return res

        return dfs(0)
