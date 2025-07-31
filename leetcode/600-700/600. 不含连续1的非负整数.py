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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def findIntegers(self, n: int) -> int:
        s = bin(n)[2:]
        N = len(s)

        @cache
        def dfs(i: int, is_hi: bool, prev_one: bool):
            if i == N:
                return 1

            res = 0
            hi = int(s[i]) if is_hi else 1
            res += dfs(i + 1, is_hi and hi == 0, False)
            if hi >= 1 and not prev_one:
                res += dfs(i + 1, is_hi and hi == 1, True)

            return res

        return dfs(0, True, False)
