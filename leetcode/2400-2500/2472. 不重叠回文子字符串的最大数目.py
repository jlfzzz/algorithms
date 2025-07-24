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
    def maxPalindromes(self, s: str, k: int) -> int:
        n = len(s)
        ok = [[False] * n for _ in range(n)]
        for i in range(n):
            ok[i][i] = True
            for j in range(i):
                if s[i] == s[j] and (j + 1 == i or ok[j + 1][i - 1]):
                    ok[j][i] = True

        @cache
        def dfs(i: int) -> int:
            if i == n:
                return 0
            res = dfs(i + 1)
            for j in range(i, n):
                if j - i + 1 >= k and ok[i][j]:
                    res = max(res, 1 + dfs(j + 1))
            return res

        return dfs(0)
