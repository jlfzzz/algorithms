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
    def longestCycle(self, edges: List[int]) -> int:
        n = len(edges)
        vis = [0] * n
        dis = [0] * n  
        ans = -1

        def dfs(i: int, d: int) -> None:
            nonlocal ans
            if vis[i] == 1:
                ans = max(ans, d - dis[i])
                return

            if vis[i] == 2:
                return

            vis[i] = 1
            dis[i] = d
            nxt = edges[i]
            if nxt != -1:
                dfs(nxt, d + 1)
            vis[i] = 2

        for i in range(n):
            if vis[i] == 0:
                dfs(i, 0)

        return ans
