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


class Solution:
    def findOrder(self, numCourses: int, prerequisites: List[List[int]]) -> List[int]:
        ans = []
        deg = [0] * numCourses
        graph = [[] for _ in range(numCourses)]
        for a, b in prerequisites:
            deg[a] += 1
            graph[b].append(a)

        dq = deque()
        for i, x in enumerate(deg):
            if x == 0:
                dq.append(i)
                ans.append(i)
                numCourses -= 1
        while dq:
            x = dq.popleft()
            for v in graph[x]:
                deg[v] -= 1
                if deg[v] == 0:
                    dq.append(v)
                    ans.append(v)
                    numCourses -= 1
        return ans if numCourses == 0 else []
