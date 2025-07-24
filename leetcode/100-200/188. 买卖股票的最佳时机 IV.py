from functools import cache
from math import inf
from typing import List


class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i: int, cnt: int, j: int) -> int:
            if cnt == k or i == n:
                return 0
            if j:
                return max(dfs(i + 1, cnt + 1, 0) + prices[i], dfs(i + 1, cnt, 1))
            return max(dfs(i + 1, cnt, 0), dfs(i + 1, cnt, 1) - prices[i])

        return dfs(0, 0, False)


class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)
        if n == 0 or k == 0:
            return 0

        # dp[i][cnt][j] 表示第i天，已完成cnt次交易，持股状态为j的最大利润
        # j=0表示不持股，j=1表示持股
        dp = [[[0 for _ in range(2)] for _ in range(k + 1)] for _ in range(n + 1)]

        # 边界条件：第n天或完成k次交易时利润为0（已经初始化为0）

        # 从后往前填表（因为原递归是从前往后，状态转移依赖后面的状态）
        for i in range(n - 1, -1, -1):
            for cnt in range(k):
                # j=1: 持股状态
                # 可以选择：卖出(cnt+1, 0) + prices[i] 或 继续持有(cnt, 1)
                dp[i][cnt][1] = max(
                    dp[i + 1][cnt + 1][0] + prices[i], dp[i + 1][cnt][1]
                )

                # j=0: 不持股状态
                # 可以选择：不买(cnt, 0) 或 买入(cnt, 1) - prices[i]
                dp[i][cnt][0] = max(dp[i + 1][cnt][0], dp[i + 1][cnt][1] - prices[i])

        return dp[0][0][0]


class Solution:
    def maxProfit(self, k: int, prices: List[int]) -> int:
        n = len(prices)
        f = [[[-inf] * 2 for _ in range(k + 2)] for _ in range(n + 1)]
        for j in range(1, k + 2):
            f[0][j][0] = 0
        for i, p in enumerate(prices):
            for j in range(1, k + 2):
                f[i + 1][j][0] = max(f[i][j][0], f[i][j][1] + p)
                f[i + 1][j][1] = max(f[i][j][1], f[i][j - 1][0] - p)
        return f[-1][-1][0]
