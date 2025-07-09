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
    def minDifficulty(self, jobDifficulty: List[int], d: int) -> int:
        n = len(jobDifficulty)
        if n < d:
            return -1

        @cache
        def dfs(i: int, use: int) -> int:
            if use > d:
                return inf
            if i == n:
                return 0 if use == d else inf

            mx = -1
            res = inf
            for j in range(i, min(n, n - d + use + 1)):
                if jobDifficulty[j] > mx:
                    mx = jobDifficulty[j]
                t = dfs(j + 1, use + 1) + mx
                if t < res:
                    res = t
            return res

        return dfs(0, 0)
