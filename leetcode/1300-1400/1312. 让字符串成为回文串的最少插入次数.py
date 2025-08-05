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
    def minInsertions(self, s: str) -> int:
        @cache
        def dfs(i, j):
            if i >= j:
                return 0
            res = inf
            if s[i] == s[j]:
                res = min(dfs(i + 1, j - 1), dfs(i + 1, j) + 1, dfs(i, j - 1) + 1)
            else:
                res = min(dfs(i + 1, j), dfs(i, j - 1)) + 1
            return res

        return dfs(0, len(s) - 1)
