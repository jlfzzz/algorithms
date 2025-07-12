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


class StockSpanner:

    def __init__(self):
        self.st = [[0, 10000000]]

    def next(self, price: int) -> int:
        ans = 1
        while price >= self.st[-1][1]:
            ans += self.st.pop()[0]
        self.st.append([ans, price])
        return ans


class StockSpanner:

    def __init__(self):
        self.dp = [[0, 10000000]]

    def next(self, price: int) -> int:
        ans = 1
        n = len(self.dp) - 1
        while n >= 0 and price >= self.dp[n][1]:
            ans += self.dp[n][0]
            n -= self.dp[n][0]
        self.dp.append([ans, price])
        return ans


# Your StockSpanner object will be instantiated and called as such:
# obj = StockSpanner()
# param_1 = obj.next(price)
