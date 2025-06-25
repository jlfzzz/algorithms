from functools import cache
from math import inf
from typing import List


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        dp = [[0, 0, 0] for _ in range(n)]
        dp[0][1] = -prices[0]
        dp[0][2] = -inf
        for i in range(1, n):
            dp[i][0] = max(dp[i - 1][0], dp[i - 1][2])
            dp[i][1] = max(dp[i - 1][0] - prices[i], dp[i - 1][1])
            dp[i][2] = dp[i - 1][1] + prices[i]
        return max(dp[n - 1][0], dp[n - 1][1], dp[n - 1][2])


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        @cache
        def dfs(i:int, status:int)->int:
            if i == n:
                return 0
            if status == 0:
                return max(dfs(i + 1, 0), dfs(i + 1, 1) - prices[i])
            if status == 1:
                return max(dfs(i + 1, 1), dfs(i + 1, 2) + prices[i])
            return dfs(i + 1, 0)
        return dfs(0, 0)
