from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
INF = int(1e9)


class Solution:
    def shortestAlternatingPaths(
        self, n: int, redEdges: List[List[int]], blueEdges: List[List[int]]
    ) -> List[int]:
        graph = [[[] for _ in range(2)] for _ in range(n)]
        for a, b in redEdges:
            graph[a][0].append(b)
        for a, b in blueEdges:
            graph[a][1].append(b)

        vis = [[False, False] for _ in range(n)]
        q = Queue()
        vis[0][0] = True
        vis[0][1] = True
        q.put((0, 0, 0))  # node, color, distance - 从红色边开始
        q.put((0, 1, 0))  # node, color, distance - 从蓝色边开始
        dis = [INF] * n
        dis[0] = 0
        while not q.empty():
            x, col, d = q.get()
            for v in graph[x][col ^ 1]:
                if not vis[v][col ^ 1]:
                    dis[v] = min(dis[v], d + 1)
                    vis[v][col ^ 1] = True
                    q.put((v, col ^ 1, d + 1))
        for i, x in enumerate(dis):
            if x == INF:
                dis[i] = -1
        return dis
