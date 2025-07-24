import queue
from typing import List


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        graph = [[] for _ in range(numCourses)]
        deg = [0] * numCourses
        for x, y in prerequisites:
            graph[y].append(x)
            deg[x] += 1

        q = queue.Queue()
        cnt = 0
        for i in range(numCourses):
            if deg[i] == 0:
                cnt += 1
                q.put(i)

        while not q.empty():
            x = q.get()
            for v in graph[x]:
                deg[v] -= 1
                if deg[v] == 0:
                    q.put(v)
                    cnt += 1
        return cnt == numCourses


class Solution:
    def canFinish(self, numCourses: int, prerequisites: List[List[int]]) -> bool:
        graph = [[] for _ in range(numCourses)]
        deg = [0] * numCourses
        for x, y in prerequisites:
            graph[y].append(x)
            deg[x] += 1

        def dfs(i: int) -> bool:
            if vis[i] == 1:
                return False

            if vis[i] == 2:
                return True

            vis[i] = 1
            res = True
            for v in graph[i]:
                res = res & dfs(v)

            vis[i] = 2
            return res

        ans = True
        vis = [0] * numCourses
        for i in range(numCourses):
            if vis[i] == 0:
                ans = ans & dfs(i)
                if not ans:
                    return False
        return ans
