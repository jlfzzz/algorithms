from math import inf
from typing import List
from functools import cache


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i: int, hold: bool) -> int:
            if i >= n:
                return 0

            if hold:  # 当前持有股票
                # 可以选择：继续持有 或 卖出
                return max(dfs(i + 1, True), dfs(i + 1, False) + prices[i])
            else:  # 当前没有股票
                # 可以选择：不买 或 买入
                return max(dfs(i + 1, False), dfs(i + 1, True) - prices[i])

        return dfs(0, False)


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [[0, 0] for _ in range(n)]
        dp[0][1] = -prices[0]
        for i in range(1, n):
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + prices[i])
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] - prices[i])
        return dp[n - 1][0]

