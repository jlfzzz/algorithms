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
    def minXor(self, nums: List[int], K: int) -> int:
        n = len(nums)
        pre = [0] * (n + 1)
        for i in range(1, n + 1):
            pre[i] = pre[i - 1] ^ nums[i - 1]

        @cache
        def dfs(i: int, k: int) -> int:
            if k == 1:
                return pre[n] ^ pre[i]

            res = INF
            for j in range(i, n - k + 1):
                res = min(res, max(pre[j + 1] ^ pre[i], dfs(j + 1, k - 1)))
            return res

        return dfs(0, K)


class Solution:
    def minXor(self, nums: List[int], K: int) -> int:
        n = len(nums)
        pre = [0] * (n + 1)
        for i in range(1, n + 1):
            pre[i] = pre[i - 1] ^ nums[i - 1]

        dp = [[INF] * (K + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(1, min(i, K) + 1):
                for k in range(i):
                    dp[i][j] = min(dp[i][j], max(pre[i] ^ pre[k], dp[k][j - 1]))
        return dp[n][K]
