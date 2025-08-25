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
    def findDiagonalOrder(self, mat: List[List[int]]) -> List[int]:
        m, n = len(mat), len(mat[0])
        ans = []

        for d in range(m + n - 1):
            t = []
            for i in range(max(0, d - n + 1), min(d, m - 1) + 1):
                j = d - i
                t.append(mat[i][j])
            if d % 2 == 0:
                ans.extend(t[::-1])
            else:
                ans.extend(t)
        return ans
