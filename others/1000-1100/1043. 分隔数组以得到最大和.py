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
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        n = len(arr)
        dp = [0] * (n + 1)

        for i in range(1, n + 1):
            mx = 0
            for j in range(i, max(0, i - k), -1):
                mx = max(mx, arr[j - 1])
                dp[i] = max(dp[i], dp[j - 1] + mx * (i - j + 1))

        return dp[n]


class Solution:
    def maxSumAfterPartitioning(self, arr: List[int], k: int) -> int:
        n = len(arr)

        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 0
            mx = -1
            res = -1
            for j in range(i, min(n, i + k)):
                mx = max(mx, arr[j])
                res = max(res, mx * (j - i + 1) + dfs(j + 1))
            return res

        return dfs(0)
