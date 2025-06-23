from typing import List


class Solution:
    def countPairsOfConnectableServers(self, edges: List[List[int]], signalSpeed: int) -> List[int]:
        n = len(edges) + 1
        ans = [0] * n
        graph = [[] for _ in range(n)]

        for e in edges:
            x, y, w = e[0], e[1], e[2]
            graph[x].append((y, w))
            graph[y].append((x, w))

        def dfs(i:int, fa:int, path:int)->None:
            nonlocal cnt
            if path % signalSpeed == 0:
                cnt += 1

            for v, d in graph[i]:
                if v != fa:
                    dfs(v, i, path + d)

        for i in range(n):
            temp1 = []
            for v, d in graph[i]:
                cnt = 0
                dfs(v, i, d)
                temp1.append(cnt)
            for j in range(len(temp1)):
                for k in range(j + 1, len(temp1)):
                    ans[i] += temp1[j] * temp1[k]
        return ans

from typing import List


class Solution:
    def countPairsOfConnectableServers(
        self, edges: List[List[int]], signalSpeed: int
    ) -> List[int]:
        n = len(edges) + 1
        ans = [0] * n
        graph = [[] for _ in range(n)]

        for e in edges:
            x, y, w = e[0], e[1], e[2]
            graph[x].append((y, w))
            graph[y].append((x, w))

        def dfs(i: int, fa: int, path: int) -> None:
            nonlocal cnt
            if path % signalSpeed == 0:
                cnt += 1

            for v, d in graph[i]:
                if v != fa:
                    dfs(v, i, path + d)

        for i in range(n):
            if len(graph[i]) == 0:
                continue
            s = 0
            for v, d in graph[i]:
                cnt = 0
                dfs(v, i, d)
                ans[i] += s * cnt
                s += cnt
            
        return ans
