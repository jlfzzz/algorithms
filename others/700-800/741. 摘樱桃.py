from ast import List
from cmath import inf
from functools import lru_cache


class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        n = len(grid)

        @lru_cache(None)
        def dfs(x1: int, y1: int, x2: int) -> int:
            y2 = x1 + y1 - x2  # 利用步数相等的约束

            # 边界检查
            if (
                x1 >= n
                or y1 >= n
                or x2 >= n
                or y2 >= n
                or y2 < 0
                or grid[x1][y1] == -1
                or grid[x2][y2] == -1
            ):
                return float("-inf")

            # 到达终点
            if x1 == n - 1 and y1 == n - 1:
                return grid[x1][y1]

            # 计算当前收集的樱桃数
            cherries = grid[x1][y1]
            if x1 != x2:  # 不在同一位置
                cherries += grid[x2][y2]

            # 尝试所有移动组合
            result = max(
                dfs(x1 + 1, y1, x2 + 1),  # 都向下
                dfs(x1 + 1, y1, x2),  # 1向下，2向右
                dfs(x1, y1 + 1, x2 + 1),  # 1向右，2向下
                dfs(x1, y1 + 1, x2),  # 都向右
            )

            return cherries + result

        result = dfs(0, 0, 0)
        return max(0, result)


class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        n = len(grid)
        f = [[[-inf] * (n + 1) for _ in range(n + 1)] for _ in range(n * 2 - 1)]
        f[0][1][1] = grid[0][0]
        for t in range(1, n * 2 - 1):
            for j in range(max(t - n + 1, 0), min(t + 1, n)):
                if grid[t - j][j] < 0:
                    continue
                for k in range(j, min(t + 1, n)):
                    if grid[t - k][k] < 0:
                        continue
                    f[t][j + 1][k + 1] = (
                        max(
                            f[t - 1][j + 1][k + 1],
                            f[t - 1][j + 1][k],
                            f[t - 1][j][k + 1],
                            f[t - 1][j][k],
                        )
                        + grid[t - j][j]
                        + (grid[t - k][k] if k != j else 0)
                    )
        return max(f[-1][n][n], 0)
