from typing import List


class Solution:
    def numberOfRightTriangles(self, grid: List[List[int]]) -> int:
        n, m = len(grid), len(grid[0])
        col = [0] * m
        for j in range(m):
            for i in range(n):
                col[j] += grid[i][j]
        res = 0
        for i in range(n):
            row = sum(grid[i])
            for j in range(m):
                if grid[i][j] == 1:
                    res += (row - 1) * (col[j] - 1)
        return res


class Solution:
    def numberOfRightTriangles(self, grid: List[List[int]]) -> int:
        col_sum = [sum(col) - 1 for col in zip(*grid)]  # 提前减一
        ans = 0
        for row in grid:
            row_sum = sum(row) - 1  # 提前减一
            ans += row_sum * sum(cs for x, cs in zip(row, col_sum) if x)
        return ans
