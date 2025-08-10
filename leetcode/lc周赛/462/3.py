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
    def maxTotal(self, value: List[int], limit: List[int]) -> int:
        n = len(value)

        arr = [[v, l] for (v, l) in zip(value, limit)]
        arr.sort(key=lambda x: (x[1], -x[0]))
        ans = 0
        prev = -1
        cnt = 0
        for i, ar in enumerate(arr):
            v, l = ar[0], ar[1]
            if l != prev:
                cnt = 0
            if l == prev and cnt == l:
                continue
            cnt += 1
            ans += v
            prev = l
        return ans
