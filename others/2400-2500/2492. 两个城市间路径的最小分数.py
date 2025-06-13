from all_algos import *


# dfs
class Solution:
    def minScore(self, n: int, roads: List[List[int]]) -> int:
        graph = [[] for _ in range(n)]
        visited = [False] * n
        ans = math.inf
        for a, b, d in roads:
            graph[a - 1].append((b - 1, d))
            graph[b - 1].append((a - 1, d))

        def dfs(curr: int, fa: int) -> None:
            nonlocal ans
            for neighbour, d in graph[curr]:
                if fa != neighbour:
                    ans = min(ans, d)
                    if not visited[neighbour]:
                        visited[neighbour] = True
                        dfs(neighbour, curr)

        dfs(0, -1)
        return ans


class Solution:
    def __init__(self):
        self.parent = []

    def find(self, x: int) -> int:
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x: int, y: int):
        self.parent[self.find(x)] = self.find(y)

    def minScore(self, n: int, roads: List[List[int]]) -> int:
        self.parent = [i for i in range(n)]

        for x, y, _ in roads:
            self.union(x - 1, y - 1)

        root_0 = self.find(0)
        min_weight = math.inf

        for x, y, w in roads:
            if self.find(x - 1) == root_0 or self.find(y - 1) == root_0:
                min_weight = min(min_weight, w)

        return min_weight
