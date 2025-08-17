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
    def new21Game(self, n: int, k: int, maxPts: int) -> float:
        if k == 0:
            return 1

        dp = [0] * (k)
        dp[0] = 1
        pre = 1
        for i in range(1, k):
            dp[i] = pre / maxPts

            pre += dp[i]
            if i - maxPts >= 0:
                pre -= dp[i - maxPts]

        for i in range(k, k + maxPts):
            dp.append(pre / maxPts)
            if i - maxPts >= 0:
                pre -= dp[i - maxPts]

        ans = 0
        for i in range(n + 1, len(dp)):
            ans += dp[i]
        return 1 - ans
