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
    def numberOfSets(self, n: int, k: int) -> int:
        dp = [[0] * (k + 1) for _ in range(n)]
        pref = [[0] * (k + 1) for _ in range(n)]
        dp[0][0] = 1
        pref[0][0] = 1

        for i in range(1, n):
            for j in range(min(i, k) + 1):
                dp[i][j] = dp[i - 1][j]
                if j - 1 >= 0:
                    dp[i][j] = (dp[i][j] + pref[i - 1][j - 1]) % MOD
                    if j - 2 >= 0:
                        dp[i][j] = (dp[i][j] - pref[j - 2][j - 1] + MOD) % MOD
                    # for l in range(j - 1, i):
                    #     dp[i][j] = (dp[i][j] + dp[l][j - 1]) % MOD
            for j in range(k + 1):
                pref[i][j] = (pref[i - 1][j] + dp[i][j]) % MOD
        return dp[n - 1][k]


class Solution:
    def numberOfSets(self, n: int, k: int) -> int:
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        pref = [[0] * (k + 1) for _ in range(n + 1)]
        dp[0][0] = 1
        for i in range(1, n + 1):
            dp[i][0] = 1
            pref[i][0] = (pref[i - 1][0] + dp[i][0]) % MOD
            up = min(k, i)
            for j in range(1, up + 1):
                dp[i][j] = (dp[i - 1][j] + pref[i - 1][j - 1]) % MOD
                pref[i][j] = (pref[i - 1][j] + dp[i][j]) % MOD
        return dp[n][k]
