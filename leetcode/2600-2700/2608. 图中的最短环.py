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


class Solution:
    def findShortestCycle(self, n: int, edges: List[List[int]]) -> int:
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        ans = float("inf")

        for start in range(n):
            vis = [-1] * n
            parent = [-1] * n
            vis[start] = 0
            dq = deque()
            dq.append(start)

            while dq:
                current = dq.popleft()
                for neighbor in graph[current]:
                    if vis[neighbor] == -1:  # 未访问过
                        vis[neighbor] = vis[current] + 1
                        parent[neighbor] = current
                        dq.append(neighbor)
                    elif parent[current] != neighbor:  # 不是父节点，找到环
                        cycle_length = vis[current] + vis[neighbor] + 1
                        ans = min(ans, cycle_length)

        return ans if ans != float("inf") else -1
