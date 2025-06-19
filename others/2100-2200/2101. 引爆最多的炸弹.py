from math import sqrt
from typing import List


class Solution:
    def maximumDetonation(self, bombs: List[List[int]]) -> int:
        n = len(bombs)
        graph = [set() for _ in range(n)]

        for i in range(n):
            x1, y1, r1 = bombs[i]
            for j in range(n):
                if i == j:
                    continue
                x2, y2, r2 = bombs[j]
                distance = sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
                if distance <= r1:
                    graph[i].add(j)

        ans = 0

        def dfs(i: int, vis: List[bool]) -> int:
            count = 1
            for v in graph[i]:
                if not vis[v]:
                    vis[v] = True
                    count += dfs(v, vis)
            return count

        for i in range(n):
            vis = [False] * n
            vis[i] = True
            ans = max(ans, dfs(i, vis))

        return ans
