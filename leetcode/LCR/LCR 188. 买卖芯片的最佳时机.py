from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def bestTiming(self, prices: List[int]) -> int:
        @cache
        def dfs(i, buy):
            if buy == 2:
                return 0
            if i == len(prices):
                return -inf
            if buy == 0:
                return max(dfs(i + 1, 0), dfs(i + 1, 1) - prices[i])
            elif buy == 1:
                return max(dfs(i + 1, 1), dfs(i + 1, 2) + prices[i])
            else:
                return 0

        return dfs(0, 0)
