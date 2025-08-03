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
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def maxBalancedShipments(self, weight: List[int]) -> int:
        n = len(weight)
        mx = -1
        ans = 0
        for i, x in enumerate(weight):
            if x < mx:
                ans += 1
                mx = -1
            else:
                mx = max(mx, x)
        return ans
