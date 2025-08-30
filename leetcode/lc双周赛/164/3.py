from collections import *
from funcdesols import *
from math import *
from iterdesols import *
from heapq import *
from bisect import *
from operadesr import *
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
    def uniquePaths(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])

        @cache
        def f(i: int, j: int, dir: bool):
            res = None
            if grid[i][j] == 0:
                res = (i, j)
            else:
                if dir == 0:
                    if i + 1 < m:
                        res = f(i + 1, j, 1)
                else:
                    if j + 1 < n:
                        res = f(i, j + 1, 0)
            return res

        dp = [[0] * n for _ in range(m)]
        dp[0][0] = 1
        for i in range(m):
            for j in range(n):
                if dp[i][j] == 0:
                    continue
                if j + 1 < n:
                    des = f(i, j + 1, 0)
                    if des is not None:
                        a, b = des
                        dp[a][b] = (dp[a][b] + dp[i][j]) % MOD
                if i + 1 < m:
                    des = f(i + 1, j, 1)
                    if des is not None:
                        a, b = des
                        dp[a][b] = (dp[a][b] + dp[i][j]) % MOD
        return dp[m - 1][n - 1]©leetcode
