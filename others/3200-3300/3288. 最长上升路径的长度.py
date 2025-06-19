from typing import List
from bisect import *


class Solution:
    def maxPathLength(self, coordinates: List[List[int]], k: int) -> int:
        kx, ky = coordinates[k][0], coordinates[k][1]
        coordinates.sort(key=lambda x: (x[0], -x[1]))
        i = 0

        ans = []
        for x, y in coordinates:
            if x == kx and y == ky:
                break

            if y >= ky or x >= kx:
                continue

            j = bisect_left(ans, y)
            if j == len(ans):
                ans.append(y)
            else:
                ans[j] = y

            i += 1

        for j in range(i + 1, len(coordinates)):
            x, y = coordinates[j][0], coordinates[j][1]
            if x <= kx or y <= ky:
                continue

            l = bisect_left(ans, y)
            if l == len(ans):
                ans.append(y)
            else:
                ans[l] = y

        return len(ans) + 1


class Solution:
    def maxPathLength(self, coordinates: List[List[int]], k: int) -> int:
        kx, ky = coordinates[k]
        coordinates.sort(key=lambda p: (p[0], -p[1]))

        g = []
        for x, y in coordinates:
            if x < kx and y < ky or x > kx and y > ky:
                j = bisect_left(g, y)
                if j < len(g):
                    g[j] = y
                else:
                    g.append(y)
        return len(g) + 1  # 算上 coordinates[k]
