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
    def minTime(self, n: int, edges: List[List[int]]) -> int:
        graph = [[] for _ in range(n)]
        for a, b, c, d in edges:
            graph[a].append((b, c, d))

        heap = []
        heapify(heap)
        heappush(heap, (0, 0))
        dis = [inf] * n
        dis[0] = 0
        while heap:
            x, t = heappop(heap)
            if x == n - 1:
                return t
            for v, a, b in graph[x]:
                if t <= b:
                    temp = t
                    if temp < a:
                        temp = a
                    if temp + 1 < dis[v]:
                        dis[v] = temp + 1
                        heappush(heap, (v, temp + 1))
        return -1
