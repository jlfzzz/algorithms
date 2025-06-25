from math import inf
from typing import List
from functools import cache

#爆内存，下面的不会
class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        n = len(prices)

        @cache
        def dfs(i: int, j: int, status: int) -> int:
            if i == n or j == k:
                return 0 if status == 0 else -inf
            if status == 0:
                return max(
                    dfs(i + 1, j, 0),
                    dfs(i + 1, j, 1) - prices[i],
                    dfs(i + 1, j, 2) + prices[i],
                )
            if status == 1:
                return max(dfs(i + 1, j, 1), dfs(i + 1, j + 1, 0) + prices[i])
            return max(dfs(i + 1, j, 2), dfs(i + 1, j + 1, 0) - prices[i])

        dfs.cache_clear()
        return dfs(0, 0, 0)


class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        n = len(prices)
        memo = [[[-1] * 3 for _ in range(k)] for _ in range(n)]

        def dfs(i: int, j: int, status: int) -> int:
            if i == n or j == k:
                return 0 if status == 0 else -inf
            if memo[i][j][status] != -1:
                return memo[i][j][status]

            res = -1
            if status == 0:
                res = max(
                    dfs(i + 1, j, 0),
                    dfs(i + 1, j, 1) - prices[i],
                    dfs(i + 1, j, 2) + prices[i],
                )
            elif status == 1:
                res = max(dfs(i + 1, j, 1), dfs(i + 1, j + 1, 0) + prices[i])
            else:
                res = max(dfs(i + 1, j, 2), dfs(i + 1, j + 1, 0) - prices[i])
            memo[i][j][status] = res
            return res
        return dfs(0, 0, 0)


class Solution:
    def maximumProfit(self, prices: List[int], k: int) -> int:
        f = [[-inf] * 3 for _ in range(k + 2)]
        for j in range(1, k + 2):
            f[j][0] = 0
        for p in prices:
            for j in range(k + 1, 0, -1):
                f[j][0] = max(f[j][0], f[j][1] + p, f[j][2] - p)
                f[j][1] = max(f[j][1], f[j - 1][0] - p)
                f[j][2] = max(f[j][2], f[j - 1][0] + p)
        return f[-1][0]
