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
    def minCost(
        self, houses: List[int], cost: List[List[int]], m: int, n: int, target: int
    ) -> int:
        if m < target:
            return -1

        @cache
        def dfs(i: int, parts: int, prev: int) -> int:
            if parts > target:
                return inf
            if i == m:
                return 0 if parts == target else inf

            res = inf
            curr_col = houses[i]

            if curr_col != 0:
                if curr_col == prev:
                    res = min(res, dfs(i + 1, parts, prev))
                else:
                    res = min(res, dfs(i + 1, parts + 1, curr_col))
                return res

            for j in range(n):
                new_col = j + 1
                if new_col == prev:
                    res = min(res, dfs(i + 1, parts, prev) + cost[i][j])
                else:
                    res = min(res, dfs(i + 1, parts + 1, new_col) + cost[i][j])

            return res

        ans = dfs(0, 0, -1)
        return ans if ans < inf else -1
