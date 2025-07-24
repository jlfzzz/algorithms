from typing import List


class C:
    def __init__(self, edges: List[List[int]]):
        n = len(edges) + 1
        m = n.bit_length() + 1
        graph = [[] for _ in range(n + 1)]
        pa = [[-1] * m for _ in range(n + 1)]
        dis = [-1] * (n + 1)

        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        def dfs(fa: int, curr: int, d) -> None:
            pa[curr][0] = fa
            for u in graph[curr]:
                if u != fa:
                    dis[u] = d + 1
                    dfs(curr, u, d + 1)

        dis[1] = 0
        dfs(-1, 1, 0)

        for x in range(m - 1):
            for i in range(1, n + 1):
                p = pa[i][x]
                if p != -1:
                    pa[i][x + 1] = pa[p][x]

        self.graph = graph
        self.pa = pa
        self.dis = dis
        self.m = m
        self.n = n

    def get_kth_ancestor(self, x: int, k: int) -> int:
        for i in range(k.bit_length() - 1, -1, -1):
            if k >> i & 1:
                x = self.pa[x][i]
        return x

    def get_lca(self, x: int, y: int) -> int:
        if self.dis[y] < self.dis[x]:
            x, y = y, x

        y = self.get_kth_ancestor(y, self.dis[y] - self.dis[x])
        if y == x:
            return x

        for i in range(self.m - 1, -1, -1):
            ax, ay = self.pa[x][i], self.pa[y][i]
            if ay != ax:
                x, y = ax, ay
        return self.pa[x][0]

    def get_dis(self, x: int, y: int) -> int:
        return self.dis[x] + self.dis[y] - 2 * self.dis[self.get_lca(x, y)]


class Solution:
    def assignEdgeWeights(
        self, edges: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        c = C(edges)

        mod = int(1e9 + 7)
        ans = []
        for a, b in queries:
            d = c.get_dis(a, b)
            if d == 0:
                ans.append(0)
                continue
            ans.append(pow(2, d - 1, mod))
        return ans
