from cmath import inf
from typing import List
from functools import cache


class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        @cache
        def dfs(i: int, j: int, k: int) -> int:
            if j < 0 or k >= n or j >= k:
                return -inf
            if i == m:
                return 0
            return (
                max(
                    dfs(i + 1, j - 1, k - 1),
                    dfs(i + 1, j, k - 1),
                    dfs(i + 1, j + 1, k - 1),
                    dfs(i + 1, j - 1, k),
                    dfs(i + 1, j, k),
                    dfs(i + 1, j + 1, k),
                    dfs(i + 1, j - 1, k + 1),
                    dfs(i + 1, j, k + 1),
                    dfs(i + 1, j + 1, k + 1),
                )
                + grid[i][j]
                + grid[i][k]
            )

        return dfs(0, 0, n - 1)


class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        m = len(grid)
        n = len(grid[0])

        # 初始化DP表
        dp = [[[0] * n for _ in range(n)] for _ in range(m)]

        # 初始化第一行
        dp[0][0][n - 1] = grid[0][0] + (grid[0][n - 1] if n > 1 else 0)

        # 填充DP表
        for i in range(1, m):
            for j in range(min(i + 1, n)):  # 机器人1的可能位置
                for k in range(max(0, n - 1 - i), n):  # 机器人2的可能位置
                    if j > k:  # 确保机器人1在机器人2左边或同一位置
                        continue

                    # 当前位置的樱桃数
                    cherries = grid[i][j] + (grid[i][k] if j != k else 0)

                    # 尝试所有可能的上一步状态
                    max_prev = 0
                    for prev_j in range(max(0, j - 1), min(n, j + 2)):
                        for prev_k in range(max(0, k - 1), min(n, k + 2)):
                            if i == 1 and (prev_j != 0 or prev_k != n - 1):
                                continue  # 第一行只能从初始位置开始
                            max_prev = max(max_prev, dp[i - 1][prev_j][prev_k])

                    dp[i][j][k] = cherries + max_prev

        # 找到最后一行的最大值
        result = 0
        for j in range(n):
            for k in range(j, n):
                result = max(result, dp[m - 1][j][k])

        return result
