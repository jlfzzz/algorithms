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
    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        n = len(fruits)
        dp = [[-inf] * n for _ in range(n)]

        s = 0
        for i in range(n):
            s += fruits[i][i]
            dp[i][i] = s

        dp[0][n - 1] = fruits[0][n - 1]
        dp[n - 1][0] = fruits[n - 1][0]
        for i in range(1, n - 1):
            for j in range(min(i + 1, n - i - 1)):
                row = n - 1 - j
                pre1, pre2, pre3 = dp[row - 1][i - 1], dp[row][i - 1], -inf
                if row + 1 < n:
                    pre3 = dp[row + 1][i - 1]

                dp[row][i] = max(pre1, pre2, pre3) + fruits[row][i]

                row = i
                col = n - 1 - j

                up1, up2, up3 = dp[row - 1][col - 1], dp[row - 1][col], -inf
                if col + 1 < n:
                    up3 = dp[row - 1][col + 1]
                dp[row][col] = max(up1, up2, up3) + fruits[row][col]

        return dp[n - 1][n - 1] + dp[n - 1][n - 2] + dp[n - 2][n - 1]
