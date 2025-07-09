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
    def maxRemovals(self, source: str, pattern: str, targetIndices: List[int]) -> int:
        n, m = len(source), len(pattern)
        target_set = set(targetIndices)
        dp = [[-float("inf")] * (m + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(m + 1):
                if dp[i - 1][j] != -float("inf"):
                    dp[i][j] = max(dp[i][j], dp[i - 1][j] + (i - 1 in target_set))
            for j in range(1, m + 1):
                if source[i - 1] == pattern[j - 1] and dp[i - 1][j - 1] != -float(
                    "inf"
                ):
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1])

        return dp[n][m] if dp[n][m] != -float("inf") else -1


class Solution:
    def maxRemovals(self, source: str, pattern: str, targetIndices: List[int]) -> int:
        targetIndices = set(targetIndices)
        n, m = len(source), len(pattern)

        @cache
        def dfs(i: int, j: int) -> int:
            if n - i < m - j:
                return -inf
            if i == n:
                return 0 if j == m else -inf
            res = dfs(i + 1, j) + (i in targetIndices)
            if j < m and source[i] == pattern[j]:
                res = max(res, dfs(i + 1, j + 1))
            return res

        ans = dfs(0, 0)
        return ans
