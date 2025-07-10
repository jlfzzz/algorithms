from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
MOD = int(1e9 + 7)


class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        @cache
        def dfs(i: int) -> int:
            if i > n:
                return 0
            res = float("inf")
            for j in range(i + 1, i * 2 + 2): 
                t = dfs(j)
                if t < res:
                    res = t 
            return res + prices[i - 1]

        return dfs(1)


class Solution:
    def minimumCoins(self, prices: List[int]) -> int:
        n = len(prices)

        @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        def dfs(i: int) -> int:
            if i * 2 >= n:
                return prices[i - 1]  # i 从 1 开始
            return min(dfs(j) for j in range(i + 1, i * 2 + 2)) + prices[i - 1]

        return dfs(1)
