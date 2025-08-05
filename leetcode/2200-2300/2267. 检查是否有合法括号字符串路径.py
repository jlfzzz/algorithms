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
    def hasValidPath(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        path = m + n - 1
        # 这个特判是速度快的基础（数据弱），没这个要23ms
        if path % 2 != 0 or grid[0][0] == ")" or grid[-1][-1] == "(":
            return False
        f = [0] * n
        f[0] = (1 << 1) if grid[0][0] == "(" else (1 >> 1)
        for j in range(1, n):
            if grid[0][j] == "(":
                f[j] = f[j - 1] << 1
            else:
                f[j] = f[j - 1] >> 1
        for i in range(1, m):
            nf = [0] * n
            nf[0] = (f[0] << 1) if grid[i][0] == "(" else (f[0] >> 1)
            for j in range(1, n):
                if grid[i][j] == "(":
                    nf[j] = (nf[j - 1] << 1) | (f[j] << 1)
                else:
                    nf[j] = (nf[j - 1] >> 1) | (f[j] >> 1)
            f = nf[:]
        if f[-1] & 1:
            return True
        return False


class Solution:
    def hasValidPath(self, grid: List[List[str]]) -> bool:
        m, n = len(grid), len(grid[0])
        path = m + n - 1
        if path % 2 != 0 or grid[0][0] == ")" or grid[-1][-1] == "(":
            return False
        dp = [[[False] * (m + n + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        dp[0][1][0] = True
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                for k in range(1, m + n + 1):
                    if grid[i - 1][j - 1] == "(":
                        dp[i][j][k] |= dp[i - 1][j][k - 1]
                        dp[i][j][k] |= dp[i][j - 1][k - 1]
                    else:
                        dp[i][j][k - 1] = dp[i - 1][j][k] or dp[i][j - 1][k]
        return dp[m][n][0]
