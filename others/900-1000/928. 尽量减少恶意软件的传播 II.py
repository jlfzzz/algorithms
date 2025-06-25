from cmath import inf
from typing import List


class Solution:
    def minMalwareSpread(self, graph: List[List[int]], initial: List[int]) -> int:
        initial.sort()
        n = len(graph)
        g = [[] for _ in range(n)]

        for i, row in enumerate(graph):
            for j, x in enumerate(row):
                if x and i != j:
                    g[i].append(j)

        ans = -1
        mx = inf

        def dfs(i: int, fa: int, deleted: int) -> None:
            nonlocal cnt
            cnt += 1
            for v in g[i]:
                if v != fa and v != deleted and vis[v] != deleted:
                    vis[v] = deleted
                    dfs(v, i, deleted)

        vis = [-1] * n
        for i, x in enumerate(initial):
            cnt = 0
            for j, y in enumerate(initial):
                if i == j or vis[y] == x:
                    continue

                vis[y] = x
                dfs(y, -1, x)
            if cnt < mx:
                mx = cnt
                ans = x
        return ans
