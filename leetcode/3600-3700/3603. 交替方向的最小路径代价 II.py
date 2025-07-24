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
    def minCost(self, m: int, n: int, waitCost: List[List[int]]) -> int:
        @cache  # 缓存装饰器，避免重复计算 dfs 的结果（记忆化）
        def dfs(i: int, j: int) -> int:
            if i < 0 or j < 0:
                return inf
            if i == 0 and j == 0:
                return 1  # 起点只有进入成本，不需要等待
            return (
                min(dfs(i, j - 1), dfs(i - 1, j)) + waitCost[i][j] + (i + 1) * (j + 1)
            )

        return dfs(m - 1, n - 1) - waitCost[-1][-1]  # 终点不需要等待
