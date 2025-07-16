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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def timeTaken(self, edges: List[List[int]]) -> List[int]:
        n = len(edges) + 1
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        max_2 = [[] for _ in range(n)]

        def dfs1(i: int, fa: int) -> int:
            max1, max2, from1, from2 = 0, 0, -1, -1

            for v in graph[i]:
                if v == fa:
                    continue

                offest = 2 - (v % 2)
                t = dfs1(v, i) + offest
                if t > max1:
                    max2, from2 = max1, from1
                    max1, from1 = t, v
                elif t > max2:
                    max2, from2 = t, v

            max_2[i] = (max1, from1, max2, from2)
            return max1

        dfs1(0, -1)

        ans = [0] * n

        def dfs2(i: int, fa: int) -> None:
            max1, from1, max2, from2 = max_2[i]
            ans[i] = max1
            offset = 2 - (i % 2)

            for v in graph[i]:
                if v == fa:
                    continue

                max_t = max1
                if v == from1:
                    max_t = max2

                max_t += offset
                if max_t > max_2[v][0]:
                    max_2[v] = (max_t, i, max_2[v][0], max_2[v][1])

                elif max_t > max_2[v][2]:
                    max_2[v] = (max_2[v][0], max_2[v][1], max_t, i)
                dfs2(v, i)

        dfs2(0, -1)
        return ans


class Solution:
    def timeTaken(self, edges: List[List[int]]) -> List[int]:
        g = [[] for _ in range(len(edges) + 1)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # nodes[x] 保存子树 x 的最大深度 max_d，次大深度 max_d2，以及最大深度要往儿子 my 走
        nodes = [None] * len(g)

        def dfs(x: int, fa: int) -> int:
            max_d = max_d2 = my = 0
            for y in g[x]:
                if y == fa:
                    continue
                depth = dfs(y, x) + 2 - y % 2  # 从 x 出发，往 my 方向的最大深度
                if depth > max_d:
                    max_d2 = max_d
                    max_d = depth
                    my = y
                elif depth > max_d2:
                    max_d2 = depth
            nodes[x] = (max_d, max_d2, my)
            return max_d

        dfs(0, -1)

        ans = [0] * len(g)

        def reroot(x: int, fa: int, from_up: int) -> None:
            max_d, max_d2, my = nodes[x]
            ans[x] = max(from_up, max_d)
            w = 2 - x % 2  # 从 y 到 x 的边权
            for y in g[x]:
                if y != fa:
                    reroot(y, x, max(from_up, max_d2 if y == my else max_d) + w)

        reroot(0, -1, 0)
        return ans
