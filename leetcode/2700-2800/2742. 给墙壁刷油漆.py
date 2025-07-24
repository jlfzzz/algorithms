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
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        n = len(cost)
        f = [0] + [inf] * n
        for c, t in zip(cost, time):
            for j in range(n, 0, -1):
                f[j] = min(f[j], f[max(j - t - 1, 0)] + c)
        return f[n]


class Solution:
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        n = len(cost)
        dp = [inf] * (n + 1)
        dp[0] = 0
        for i in range(1, n + 1):
            c, t = cost[i - 1], time[i - 1]
            for j in range(n, -1, -1):
                dp[j] = min(dp[max(0, j - t - 1)] + c, dp[j])
        return dp[n]


class Solution:
    def paintWalls(self, cost: List[int], time: List[int]) -> int:
        n = len(cost)
        dp = [[inf] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        for i in range(1, n + 1):
            c, t = cost[i - 1], time[i - 1]
            for j in range(n, -1, -1):
                dp[i][j] = min(dp[i - 1][j], dp[i - 1][max(0, j - t - 1)] + c)
        return dp[n][n]
