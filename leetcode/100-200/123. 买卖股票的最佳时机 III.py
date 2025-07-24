from typing import List
from functools import *


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i: int, cnt: int, buy: int) -> int:
            if i == n or cnt == 2:
                return 0
            if buy:
                return max(dfs(i + 1, cnt + 1, 0) + prices[i], dfs(i + 1, cnt, 1))
            return max(dfs(i + 1, cnt, 0), dfs(i + 1, cnt, 1) - prices[i])

        return dfs(0, 0, 0)


class Solution:
    def maxProfit(self, prices: List[int]) -> int:
        n = len(prices)
        memo = [[[-1] * 2 for _ in range(2)] for _ in range(n)]

        def dfs(i: int, cnt: int, buy: int) -> int:
            if i == n or cnt == 2:
                return 0
            if memo[i][cnt][buy] != -1:
                return memo[i][cnt][buy]

            res = 0
            if buy:
                res = max(dfs(i + 1, cnt + 1, 0) + prices[i], dfs(i + 1, cnt, 1))
                memo[i][cnt][buy] = res
                return res

            res = max(dfs(i + 1, cnt, 0), dfs(i + 1, cnt, 1) - prices[i])
            memo[i][cnt][buy] = res
            return res

        return dfs(0, 0, 0)
