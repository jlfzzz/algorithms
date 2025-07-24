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
    def maximumScore(self, scores: List[int], edges: List[List[int]]) -> int:
        n = len(scores)
        graph = [[] for _ in range(n)]

        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        for i in range(n):
            graph[i].sort(key=lambda x: scores[x], reverse=True)
            if len(graph[i]) > 3:
                graph[i] = graph[i][:3]

        ans = -1

        for a, b in edges:
            # 对于边(a,b)，寻找最佳的c和d
            for c in graph[a]:
                if c != b:  # c不能是b
                    for d in graph[b]:
                        if d != a and d != c:  # d不能是a或c
                            score = scores[a] + scores[b] + scores[c] + scores[d]
                            ans = max(ans, score)

        return ans


class Solution:
    def maximumScore(self, scores: List[int], edges: List[List[int]]) -> int:
        g = [[] for _ in range(len(scores))]
        for x, y in edges:
            g[x].append((scores[y], y))
            g[y].append((scores[x], x))
        for i, vs in enumerate(g):
            if len(vs) > 3:
                g[i] = nlargest(3, vs)

        ans = -1
        for x, y in edges:
            for score_a, a in g[x]:
                for score_b, b in g[y]:
                    if y != a != b != x:
                        ans = max(ans, score_a + scores[x] + scores[y] + score_b)
        return ans
