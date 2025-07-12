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
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        n = len(quiet)
        graph = [[] for _ in range(n)]
        deg = [0] * n
        for a, b in richer:
            graph[a].append(b)
            deg[b] += 1

        dq = deque()
        for i, x in enumerate(deg):
            if x == 0:
                dq.append(i)

        mx = [i for i in range(n)]
        while dq:
            x = dq.popleft()
            for v in graph[x]:
                deg[v] -= 1
                if quiet[mx[x]] < quiet[mx[v]]:
                    mx[v] = mx[x]
                if deg[v] == 0:
                    dq.append(v)
        return mx


class Solution:
    def loudAndRich(self, richer: List[List[int]], quiet: List[int]) -> List[int]:
        n = len(quiet)
        graph = [[] for _ in range(n)]
        for a, b in richer:
            graph[b].append(a)

        def dfs(i: int):
            for v in graph[i]:
                nonlocal t
                if quiet[v] < quiet[t]:
                    t = v
                dfs(v)

        ans = []
        for i in range(n):
            t = i
            dfs(i)
            ans.append(t)
        return ans
