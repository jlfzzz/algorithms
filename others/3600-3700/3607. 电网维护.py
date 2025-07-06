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
    def processQueries(
        self, c: int, connections: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        g = [[] for _ in range(c + 1)]
        for x, y in connections:
            g[x].append(y)
            g[y].append(x)

        belong = [-1] * (c + 1)
        heaps = []

        def dfs(x: int) -> None:
            belong[x] = len(heaps)  # 记录节点 x 在哪个堆
            h.append(x)
            for y in g[x]:
                if belong[y] < 0:
                    dfs(y)

        for i in range(1, c + 1):
            if belong[i] >= 0:
                continue
            h = []
            dfs(i)
            heapify(h)
            heaps.append(h)

        ans = []
        offline = [False] * (c + 1)
        for op, x in queries:
            if op == 2:
                offline[x] = True
                continue
            if not offline[x]:
                ans.append(x)
                continue
            h = heaps[belong[x]]
            # 懒删除：取堆顶的时候，如果离线，才删除
            while h and offline[h[0]]:
                heappop(h)
            ans.append(h[0] if h else -1)
        return ans
