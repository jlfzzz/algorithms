from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def palindromePartition(self, s: str, k: int) -> int:
        n = len(s)

        cost = [[0] * n for _ in range(n)]
        for l in range(n - 1, -1, -1):
            for r in range(l + 1, n):
                if s[l] == s[r]:
                    cost[l][r] = cost[l + 1][r - 1]
                else:
                    cost[l][r] = cost[l + 1][r - 1] + 1

        @cache
        def dfs(i: int, parts: int) -> int:
            if n - i < k - parts:
                return float("inf")
            if parts == k:
                return 0 if i == n else float("inf")

            res = float("inf")
            for j in range(i, n):
                res = min(res, cost[i][j] + dfs(j + 1, parts + 1))
            return res

        return dfs(0, 0)
