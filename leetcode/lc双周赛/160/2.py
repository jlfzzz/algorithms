from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]


class Solution:
    def minCost(self, m: int, n: int, waitCost: List[List[int]]) -> int:
        q = []
        q = Queue()
        t = 1
        q.put((0, 0, 0))
        dis = [[inf] * n for _ in range(m)]
        while q:
            n = len(q)
            for i in range(n):
                x, y, c = q.get()
                if x == m - 1 and y == n - 1:
                    continue
                if t % 2:
                    new_x1, new_y1 = x + 1, y
                    new_x2, new_y2 = x, y + 1

                    def valid(x, y):
                        return x >= 0 and x < m and y >= 0 and y < n

                    cost1, cost2 = (new_x1 + 1) * (new_y1 + 1), (new_x2 + 1) * (
                        new_y2 + 1
                    )
                    if valid(new_x1, new_y1) and cost1 < dis[new_x1][new_y1]:
                        dis[new_x1][new_y1] = cost1
                        q.put((new_x1, new_y1, cost1))
                    if valid(new_x2, new_y2) and cost2 < dis[new_x2][new_y2]:
                        dis[new_x2][new_y2] = cost2
                        q.put((new_x2, new_y2, cost2))
                else:
                    c += waitCost[x][y]
                    q.put((x, y, c))
                    dis[x][y] = c
        return dis[m - 1][n - 1]
