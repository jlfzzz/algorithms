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
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        n = len(nums)

        @cache
        def dfs(i: int, left: int) -> float:
            if left < 0:
                return -inf
            if i == n:
                return 0

            s = 0
            res = -inf
            for j in range(i, n):
                s += nums[j]
                res = max(res, s / (j - i + 1) + dfs(j + 1, left - 1))
            return res

        return dfs(0, k)


class Solution:
    def largestSumOfAverages(self, nums: List[int], k: int) -> float:
        n = len(nums)
        prefix = [0] + list(accumulate(nums))

        dp = [[0.0] * (k + 1) for _ in range(n + 1)]

        for i in range(1, n + 1):
            dp[i][1] = prefix[i] / i

            for j in range(2, min(k, i) + 1):
                for x in range(j - 1, i):
                    avg = (prefix[i] - prefix[x]) / (i - x)
                    dp[i][j] = max(dp[i][j], dp[x][j - 1] + avg)

        return dp[n][k]
