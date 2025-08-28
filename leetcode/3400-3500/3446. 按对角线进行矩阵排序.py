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
    def sortMatrix(self, grid: List[List[int]]) -> List[List[int]]:
        n = len(grid)
        for row in range(n):
            cord = []
            val = []
            for d in range(n):
                x, y = row + d, d
                if not (x >= 0 and x < n and y >= 0 and y < n):
                    break
                cord.append((x, y))
                val.append(grid[x][y])
            val.sort()
            val = val[::-1]
            for i, (a, b) in enumerate(cord):
                grid[a][b] = val[i]

        for col in range(1, n):
            cord = []
            val = []
            for d in range(n):
                x, y = d, col + d
                if not (x >= 0 and x < n and y >= 0 and y < n):
                    break
                cord.append((x, y))
                val.append(grid[x][y])
            val.sort()
            for i, (a, b) in enumerate(cord):
                grid[a][b] = val[i]
        return grid
