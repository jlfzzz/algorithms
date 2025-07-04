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
