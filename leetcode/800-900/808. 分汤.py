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
    def soupServings(self, n: int) -> float:
        if n > 4800:
            return 1.0
        n = (n + 24) // 25

        @cache
        def dfs(a, b):
            if a <= 0 and b <= 0:
                return 0.5
            if a <= 0:
                return 1.0
            if b <= 0:
                return 0.0
            return 0.25 * (
                dfs(a - 4, b)
                + dfs(a - 3, b - 1)
                + dfs(a - 2, b - 2)
                + dfs(a - 1, b - 3)
            )

        return dfs(n, n)
