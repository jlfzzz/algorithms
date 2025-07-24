from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
INF = int(1e9)


class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        is_p = [[False] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            for j in range(i, n):
                if s[i] == s[j] and (j - i < 2 or is_p[i + 1][j - 1]):
                    is_p[i][j] = True

        dp = [INF] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            for j in range(i):
                if is_p[j][i - 1]:
                    dp[i] = min(dp[i], dp[j] + 1)
        return dp[n] - 1


class Solution:
    def minCut(self, s: str) -> int:
        n = len(s)
        # 预处理回文子串
        is_pal = [[False] * n for _ in range(n)]
        for i in range(n - 1, -1, -1):
            for j in range(i, n):
                if s[i] == s[j] and (j - i < 2 or is_pal[i + 1][j - 1]):
                    is_pal[i][j] = True

        # dp[i]: s[:i] 的最小切割数
        dp = [float("inf")] * (n + 1)
        dp[0] = -1  # 空串前切一次，回头 +1 抵消

        for i in range(1, n + 1):
            for j in range(i):
                if is_pal[j][i - 1]:
                    dp[i] = min(dp[i], dp[j] + 1)
        return dp[n]


