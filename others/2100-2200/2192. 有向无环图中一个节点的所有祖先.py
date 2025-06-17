from typing import List
import heapq


class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        graph = [[] for _ in range(n)]
        deg = [0] * n
        for a, b in edges:
            graph[a].append(b)
            deg[b] += 1

        heap = []

        for i, x in enumerate(deg):
            if x == 0:
                heapq.heappush(heap, i)

        ans = [set() for _ in range(n)]
        while heap:
            u = heapq.heappop(heap)
            for v in graph[u]:
                ans[v].add(u)
                ans[v].update(ans[u])
                deg[v] -= 1
                if deg[v] == 0:
                    heapq.heappush(heap, v)
        return [sorted(list(x)) for x in ans]


class Solution:
    def getAncestors(self, n: int, edges: List[List[int]]) -> List[List[int]]:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[y].append(x)  

        def dfs(x: int) -> None:
            vis[x] = True 
            for y in g[x]:
                if not vis[y]:
                    dfs(y)  

        ans = [None] * n
        for i in range(n):
            vis = [False] * n
            dfs(i)  
            vis[i] = False  
            ans[i] = [j for j, b in enumerate(vis) if b]
        return ans
