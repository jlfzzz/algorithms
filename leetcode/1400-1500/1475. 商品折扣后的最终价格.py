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
    def finalPrices(self, prices: List[int]) -> List[int]:
        n = len(prices)
        dq = deque()
        ans = [0] * n
        for i, x in enumerate(prices):
            while dq and prices[dq[-1]] >= x:
                y = dq.pop()
                ans[y] = prices[y] - x
            dq.append(i)
        while dq:
            x = dq.pop()
            ans[x] = prices[x]
        return ans
