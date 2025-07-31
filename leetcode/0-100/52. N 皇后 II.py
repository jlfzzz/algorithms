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
    def totalNQueens(self, n: int) -> int:
        # queen = [0] * n
        col = [True] * n
        diag1 = [True] * (2 * n - 1)
        diag2 = [True] * (2 * n - 1)
        ans = 0

        def dfs(row: int):
            if row == n:
                nonlocal ans
                ans += 1
                return
            for i in range(n):
                if col[i] and diag1[row + i] and diag2[i - row + n - 1]:
                    diag1[row + i] = False
                    diag2[i - row + n - 1] = False
                    col[i] = False
                    dfs(row + 1)
                    diag1[row + i] = True
                    diag2[i - row + n - 1] = True
                    col[i] = True

        dfs(0)
        return ans
