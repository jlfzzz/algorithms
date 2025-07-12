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
    def maxProductPath(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])
        MOD = 10**9 + 7

        # dp[i][j][0] 存储最大值，dp[i][j][1] 存储最小值
        dp = [[[-inf, inf] for _ in range(n)] for _ in range(m)]

        # 初始化起始点
        dp[0][0] = [grid[0][0], grid[0][0]]

        for j in range(1, n):
            x = grid[0][j]
            candidates = [x * dp[0][j - 1][0], x * dp[0][j - 1][1]]
            dp[0][j][0] = max(candidates)
            dp[0][j][1] = min(candidates)

        # 正确的第一列初始化
        for i in range(1, m):
            x = grid[i][0]
            candidates = [x * dp[i - 1][0][0], x * dp[i - 1][0][1]]
            dp[i][0][0] = max(candidates)
            dp[i][0][1] = min(candidates)

        # 填充剩余位置
        for i in range(1, m):
            for j in range(1, n):
                x = grid[i][j]
                candidates = [
                    x * dp[i - 1][j][0],  # 从上方来的最大值
                    x * dp[i - 1][j][1],  # 从上方来的最小值
                    x * dp[i][j - 1][0],  # 从左方来的最大值
                    x * dp[i][j - 1][1],  # 从左方来的最小值
                ]
                dp[i][j][0] = max(candidates)
                dp[i][j][1] = min(candidates)

        result = dp[m - 1][n - 1][0]
        return result % MOD if result >= 0 else -1
