from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

MOD = int(1e9 + 7)
DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]

from collections import defaultdict, deque


class Solution:
    def checkIfPrerequisite(
        self, n: int, prerequisites: List[List[int]], queries: List[List[int]]
    ) -> List[bool]:
        # Step 1: Build graph and in-degree
        graph = defaultdict(list)
        indegree = [0] * n
        for u, v in prerequisites:
            graph[u].append(v)
            indegree[v] += 1

        # Step 2: Each course's prerequisite set
        pre = [set() for _ in range(n)]

        # Step 3: Topological sort
        q = deque(i for i in range(n) if indegree[i] == 0)

        while q:
            u = q.popleft()
            for v in graph[u]:
                # u 是 v 的前驱，且 u 的前驱也是 v 的前驱
                pre[v].update(pre[u])
                pre[v].add(u)
                indegree[v] -= 1
                if indegree[v] == 0:
                    q.append(v)

        # Step 4: Answer queries
        return [a in pre[b] for a, b in queries]


class Solution:
    def checkIfPrerequisite(
        self, n: int, prerequisites: List[List[int]], queries: List[List[int]]
    ) -> List[bool]:
        f = [[False] * n for _ in range(n)]
        for a, b in prerequisites:
            f[a][b] = True
        for k in range(n):
            for i in range(n):
                for j in range(n):
                    if f[i][k] and f[k][j]:
                        f[i][j] = True
        return [f[a][b] for a, b in queries]


class Solution:
    def checkIfPrerequisite(self, numCourses: int, prerequisites: List[List[int]], queries: List[List[int]]) -> List[bool]:
        graph =[[] for _ in range(numCourses)]
        for a, b in prerequisites:
            graph[a].append(b)

        def dfs(i:int)->bool:
            if i == target:
                return True
            for v in graph[i]:
                if not vis[v]:
                    vis[v] = True
                    if dfs(v):
                        return True
            return False

        ans = []
        for a, b in queries:
            vis = [False] * numCourses
            vis[a] = True
            target = b
            ans.append(dfs(a))
        return ans
