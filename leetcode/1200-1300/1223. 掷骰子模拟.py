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
    def dieSimulator(self, n: int, rollMax: List[int]) -> int:

        @cache
        def dfs(i, pre, cnt) -> int:
            if i == n:
                return 1
            res = 0
            for j in range(1, 7):
                if j != pre:
                    res += dfs(i + 1, j, 1)
                else:
                    if cnt < rollMax[j - 1]:
                        res += dfs(i + 1, j, cnt + 1)
            return res % MOD

        return dfs(0, -1, 0)
