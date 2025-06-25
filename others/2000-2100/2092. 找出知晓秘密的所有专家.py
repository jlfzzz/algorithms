from math import inf
from typing import Dict, List
from heapq import *


class Solution:
    def findAllPeople(
        self, n: int, meetings: List[List[int]], firstPerson: int
    ) -> List[int]:
        graph = [[] for _ in range(n)]
        for a, b, t in meetings:
            graph[a].append((b, t))
            graph[b].append((a, t))

        h = []
        heapify(h)
        heappush(h, (0, 0))
        heappush(h, (0, firstPerson))
        vis = [inf] * n
        vis[0] = 0
        vis[firstPerson] = 0
        while h:
            [t, person] = heappop(h)

            for v, t2 in graph[person]:
                if t > t2:
                    continue
                if vis[v] == inf or t2 < vis[v]:
                    vis[v] = t2
                    heappush(h, (t2, v))
        ans = [i for i, x in enumerate(vis) if x != inf]
        return ans


class Solution:
    def findAllPeople(
        self, n: int, meetings: List[List[int]], firstPerson: int
    ) -> List[int]:
        # 将 meetings 按时间排序
        meetings.sort(key=lambda x: x[2])

        # 根据时间先后，为每个时刻构建一个邻接表,置于列表中。考虑到本就是稀疏图并再次拆分，非常分散，故每个邻接表都用 hash map。
        multiAdj = []
        for i in range(len(meetings)):
            if i == 0 or meetings[i][2] > meetings[i - 1][2]:
                multiAdj.append({})
            adj = multiAdj[-1]
            u, v, time = meetings[i]
            if u not in adj:
                adj[u] = []
            if v not in adj:
                adj[v] = []
            adj[u].append(v)
            adj[v].append(u)

        visited = [False] * n
        visited[0] = True
        visited[firstPerson] = True

        def dfs(u: int, adj: Dict[int, List[int]]):
            for v in adj.get(u, []):
                if not visited[v]:
                    visited[v] = True
                    dfs(v, adj)

        for adj in multiAdj:
            # 选取访问过的点 dfs 向外扩散，此处切忌遍历 0～n-1
            for p in adj.keys():
                if visited[p]:
                    dfs(p, adj)

        # 筛选访问过的点构成结果，即所有知晓秘密的专家
        return [i for i in range(n) if visited[i]]
