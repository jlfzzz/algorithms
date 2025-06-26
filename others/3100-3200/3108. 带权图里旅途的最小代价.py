from typing import List


class UnionFind:
    def __init__(self, n: int):
        self.n = n
        pa = [i for i in range(n)]
        weight = [(1 << 24) - 1] * n
        rank = [1] * n
        self.pa = pa
        self.weight = weight
        self.rank = rank

    def find(self, x: int) -> int:
        if self.pa[x] != x:
            self.pa[x] = self.find(self.pa[x])
        return self.pa[x]

    def union(self, x: int, y: int, w: int) -> None:
        ax, ay = self.find(x), self.find(y)
        if ax == ay:
            self.weight[ax] &= w
            return
        if self.rank[ax] == self.rank[ay]:
            self.rank[ax] += 1
            self.weight[ax] &= w
            self.weight[ax] &= self.weight[ay]
            self.pa[ay] = ax
        elif self.rank[ax] > self.rank[ay]:
            self.weight[ax] &= w
            self.weight[ax] &= self.weight[ay]
            self.pa[ay] = ax
        else:
            self.weight[ay] &= w
            self.weight[ay] &= self.weight[ax]
            self.pa[ax] = ay


class Solution:
    def minimumCost(
        self, n: int, edges: List[List[int]], query: List[List[int]]
    ) -> List[int]:
        uf = UnionFind(n)
        for edge in edges:
            a, b, w = edge[0], edge[1], edge[2]
            uf.union(a, b, w)

        ans = []
        for a, b in query:
            if uf.find(a) != uf.find(b):
                ans.append(-1)
                continue
            ans.append(uf.weight[uf.find(a)])
        return ans


class Solution:
    def minimumCost(
        self, n: int, edges: List[List[int]], query: List[List[int]]
    ) -> List[int]:
        g = [[] for _ in range(n)]
        for x, y, w in edges:
            g[x].append((y, w))
            g[y].append((x, w))

        def dfs(x: int) -> int:
            and_ = -1
            ids[x] = len(cc_and)  # 记录每个点所在连通块的编号，用长度来判断编号
            for y, w in g[x]:
                and_ &= w
                if ids[y] < 0:  # 没有访问过
                    and_ &= dfs(y)
            return and_

        ids = [-1] * n  # 记录每个点所在连通块的编号
        cc_and = []  # 记录每个连通块的边权的 AND
        for i in range(n):
            if ids[i] < 0:
                cc_and.append(dfs(i))

        return [-1 if ids[s] != ids[t] else cc_and[ids[s]] for s, t in query]
