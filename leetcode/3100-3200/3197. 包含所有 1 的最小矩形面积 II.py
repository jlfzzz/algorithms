from math import inf
from typing import List


class Solution:
    def minimumSum(self, grid: List[List[int]]) -> int:

        def minimumArea(grid: List[List[int]]) -> int:
            n, m = len(grid), len(grid[0])
            l, r, t, d = inf, 0, inf, 0
            ans = 0
            for i, x in enumerate(grid):
                for j, y in enumerate(x):
                    if y:
                        l = min(l, j)
                        r = max(r, j)
                        t = min(t, i)
                        d = max(d, i)
            ans = (r - l + 1) * (d - t + 1)
            return ans

        # 三个
        def f(grid: List[List[int]]):
            n, m = len(grid), len(grid[0])
            if n <= 2:
                return inf
            ans = inf
            for i in range(1, n - 1):
                for j in range(i, n - 1):
                    ans = min(
                        ans,
                        minimumArea(grid[:i])
                        + minimumArea(grid[i : j + 1])
                        + minimumArea(grid[j + 1 : n]),
                    )
            return ans

        def f2(grid: List[List[int]]):
            n, m = len(grid), len(grid[0])
            if n <= 1 or m <= 1:
                return inf
            ans = inf
            for cut in range(1, m):
                left = [row[:cut] for row in grid]
                right = [row[cut:] for row in grid]
                rn = len(right)
                for i in range(1, rn):
                    upper = right[:i]
                    lower = right[i:]
                    ans = min(
                        ans, minimumArea(left) + minimumArea(upper) + minimumArea(lower)
                    )
            return ans

        def rotate(grid: List[List[int]]) -> List[List[int]]:
            return [list(row) for row in zip(*grid[::-1])]

        ans = inf
        g = grid
        for _ in range(4):
            ans = min(ans, f(g), f2(g))
            g = rotate(g)

        return ans
