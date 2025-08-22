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
            
