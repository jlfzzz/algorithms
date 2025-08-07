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
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def minimumDistance(self, word: str) -> int:
        n = len(word)

        pos = defaultdict(tuple)

        for c in ascii_uppercase:
            d = ord(c) - ord("A")
            x = d // 6
            y = d % 6
            pos[d] = (x, y)

        dis = [[0] * 26 for _ in range(26)]
        for i in range(26):
            for j in range(26):
                a, b, c, d = pos[i][0], pos[i][1], pos[j][0], pos[j][1]
                dx, dy = abs(c - a), abs(d - b)
                dis[i][j] = dx + dy

        @cache
        def dfs(i, a, b) -> int:
            if i == n:
                return 0

            j = ord(word[i]) - ord("A")
            return min(dfs(i + 1, j, b) + dis[a][j], dfs(i + 1, a, j) + dis[b][j])

        ans = inf
        for i in range(26):
            for j in range(26):
                ans = min(ans, dfs(0, i, j))
        return ans
