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
    def maxScore(self, a: List[int], b: List[int]) -> int:
        n = len(b)
        dp = [[-inf] * (n + 1) for _ in range(5)]
        for i in range(n + 1):
            dp[0][i] = 0

        for i in range(1, 5):
            for j in range(1, n + 1):
                dp[i][j] = max(dp[i][j - 1], dp[i - 1][j - 1] + a[i - 1] * b[j - 1])
        return dp[4][n]
