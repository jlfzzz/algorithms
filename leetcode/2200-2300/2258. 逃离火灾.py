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
    def maximumMinutes(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        fires = []
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                if x == 1:
                    fires.append((i, j))

        fire_timestamp = [[inf] * n for _ in range(m)]
        dq = deque()
        for x, y in fires:
            dq.append((x, y, 0))
            fire_timestamp[x][y] = 0

        def ok(i, j):
            return i >= 0 and i < m and j >= 0 and j < n

        while dq:
            x, y, t = dq.popleft()

            for dx, dy in DIRS:
                i, j = x + dx, y + dy
                if ok(i, j) and fire_timestamp[i][j] > t + 1 and grid[i][j] != 2:
                    fire_timestamp[i][j] = t + 1
                    dq.append((i, j, t + 1))

        def check(start_time):
            q = deque()
            q.append((0, 0, start_time))
            visited = [[False] * n for _ in range(m)]
            visited[0][0] = True

            while q:
                x, y, t = q.popleft()
                if x == m - 1 and y == n - 1:
                    return True

                for dx, dy in DIRS:
                    i, j = x + dx, y + dy
                    if ok(i, j) and grid[i][j] != 2 and not visited[i][j]:
                        if (i, j) == (m - 1, n - 1):
                            if t + 1 <= fire_timestamp[i][j]:
                                visited[i][j] = True
                                q.append((i, j, t + 1))
                        else:
                            if t + 1 < fire_timestamp[i][j]:
                                visited[i][j] = True
                                q.append((i, j, t + 1))
            return False

        ans = -1
        lo = 0
        hi = int(1e9) + 1

        while lo < hi:
            mid = (lo + hi) // 2
            if check(mid):
                lo = mid + 1
                ans = mid
            else:
                hi = mid
        return ans
