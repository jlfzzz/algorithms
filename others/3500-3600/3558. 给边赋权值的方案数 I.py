from typing import List


class Solution:
    def assignEdgeWeights(self, edges: List[List[int]]) -> int:
        MOD = 1_000_000_007
        n = len(edges) + 1
        g = [[] for _ in range(n + 1)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        def dfs(x: int, fa: int) -> int:
            d = 0
            for y in g[x]:
                if y != fa:  # 不递归到父节点
                    d = max(d, dfs(y, x) + 1)
            return d

        k = dfs(1, 0)
        return pow(2, k - 1, MOD)
