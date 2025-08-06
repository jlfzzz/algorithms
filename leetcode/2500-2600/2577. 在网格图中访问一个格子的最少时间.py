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
    def minimumTime(self, grid: List[List[int]]) -> int:
        m, n = len(grid), len(grid[0])
        if grid[0][1] > 1 and grid[1][0] > 1:
            return -1

        def ok(a, b):
            return a >= 0 and a < m and b >= 0 and b < n

        time = [[INF] * n for _ in range(m)]
        time[0][0] = 0
        h = []
        heappush(h, (0, 0, 0))

        while h:
            t, x, y = heappop(h)
            if x == m - 1 and y == n - 1:
                return t
            if t > time[x][y]:
                continue

            for dx, dy in DIRS:
                a, b = x + dx, y + dy
                if ok(a, b):
                    if t + 1 >= grid[a][b]:
                        if t + 1 < time[a][b]:
                            time[a][b] = t + 1
                            heappush(h, (t + 1, a, b))
                    else:
                        if (t & 1) != (grid[a][b] & 1):
                            arrival_time = grid[a][b]
                        else:
                            arrival_time = grid[a][b] + 1

                        if arrival_time < time[a][b]:
                            time[a][b] = arrival_time
                            heappush(h, (arrival_time, a, b))
