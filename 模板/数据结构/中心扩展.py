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
INF = float('inf')
MOD = int(1e9 + 7)


# 3615. 图中的最长回文路径
# 中心扩展图中找回文串 + 状压dp + 剪枝
class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        ans = 0
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # 二进制状压vis
        @cache
        def dfs(left: int, right: int, vis: int) -> int:
            res = 0
            for v in g[left]:
                if vis >> v & 1:
                    continue
                for w in g[right]:
                    if vis >> w & 1 == 0 and v != w and label[w] == label[v]:
                        # 必须加，不然超时
                        # 因为当前左和右不影响，对称的
                        if v > w:
                            v, w = w, v
                        res = Max(res, dfs(v, w, vis | 1 << v | 1 << w) + 2)

        for i in range(n):
            ans = Max(ans, dfs(i, i, 1 << i) + 1)
        for a, b in edges:
            if label[a] == label[b]:
                ans = Max(ans, dfs(a, b, 1 << a | 1 << b) + 2)
        return ans
