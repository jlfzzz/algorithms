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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def calculateMinimumHP(self, dungeon: List[List[int]]) -> int:
        m, n = len(dungeon), len(dungeon[0])
        dp = [[inf] * (n + 1) for _ in range(m + 1)]

        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                if i == m - 1 and j == n - 1:
                    dp[i][j] = 1 if dungeon[i][j] >= 0 else -dungeon[i][j] + 1
                else:
                    if dungeon[i][j] < 0:
                        dp[i][j] = min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j]
                    else:
                        dp[i][j] = max(
                            1,
                            min(
                                dp[i + 1][j] - dungeon[i][j],
                                dp[i][j + 1] - dungeon[i][j],
                            ),
                        )
        return dp[0][0]
