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
    def checkPartitioning(self, s: str) -> bool:
        n = len(s)
        is_p = [[False] * n for _ in range(n)]
        for i in range(n):
            is_p[i][i] = True
            for j in range(i):
                if s[i] == s[j] and (i == j + 1 or is_p[j + 1][i - 1]):
                    is_p[j][i] = True

        dp = [[False] * 4 for _ in range(n + 1)]
        dp[0][0] = True
        for i in range(1, n + 1):
            for j in range(1, 4):
                for k in range(1, i + 1):
                    if is_p[k - 1][i - 1] and dp[k - 1][j - 1]:
                        dp[i][j] = True
        return dp[n][3]


class Solution:
    def checkPartitioning(self, s: str) -> bool:
        n = len(s)
        is_p = [[False] * n for _ in range(n)]
        for i in range(n):
            is_p[i][i] = True
            for j in range(i):
                if s[i] == s[j] and (i == j + 1 or is_p[j + 1][i - 1]):
                    is_p[j][i] = True

        @cache
        def dfs(i: int, use: int) -> bool:
            if use > 3:
                return False
            if i == n:
                return use == 3
            res = False
            for j in range(i, n):
                if is_p[i][j]:
                    res |= dfs(j + 1, use + 1)
            return res

        return dfs(0, 0)
