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
    def sumOfDistancesInTree(self, n: int, edges: List[List[int]]) -> List[int]:
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        dp1 = [0] * n
        cnt_nodes = [1] * n

        def dfs1(i: int, fa: int) -> int:
            res = 0
            for v in graph[i]:
                if v != fa:
                    t = dfs1(v, i) + cnt_nodes[v]
                    res += t
                    cnt_nodes[i] += cnt_nodes[v]

            dp1[i] = res
            return res

        dfs1(0, -1)
        ans = [0] * n

        def dfs2(i: int, fa: int) -> None:
            ans[i] = dp1[i]
            for v in graph[i]:
                if v != fa:
                    dp1[v] = dp1[i] - cnt_nodes[v] + (n - cnt_nodes[v])
                    dfs2(v, i)

        dfs2(0, -1)
        return ans
