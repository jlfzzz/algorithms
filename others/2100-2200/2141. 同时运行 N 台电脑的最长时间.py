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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        l, r = 0, sum(batteries) // n + 1
        while l + 1 < r:
            x = (l + r) // 2
            if n * x <= sum(min(b, x) for b in batteries):
                l = x
            else:
                r = x
        return l


class Solution:
    def maxRunTime(self, n: int, batteries: List[int]) -> int:
        batteries.sort(reverse=True)
        s = sum(batteries)
        for b in batteries:
            if b <= s // n:
                return s // n
            s -= b
            n -= 1
