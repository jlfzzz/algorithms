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


class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)

        @cache
        def dfs(i: int, buy: int) -> int:
            if i == n:
                return 0 if not buy else -inf
            if not buy:
                return max(dfs(i + 1, 0), dfs(i + 1, 1) - prices[i])
            return max(dfs(i + 1, 1), dfs(i + 1, 0) + prices[i] - fee)

        return dfs(0, 0)


class Solution:
    def maxProfit(self, prices: List[int], fee: int) -> int:
        n = len(prices)
        dp = [[-inf, -inf] for _ in range(n + 1)]
        dp[0][0] = 0
        for i in range(1, n + 1):
            price = prices[i - 1]
            dp[i][0], dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + price - fee), max(
                dp[i - 1][1], dp[i - 1][0] - price
            )
        return dp[n][0]
