from collections import *
from functools import *
import heapq
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
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        if sx == tx and sy == ty:
            return 0
        if sx > tx or sy > ty:
            return -1

        def dfs(x: int, y: int) -> int:
            if x < sx or y < sy:
                return inf
            if x == sx and y == sy:
                return 0
            if (x == 0 and sx != 0) or (y == 0 and sy != 0):
                return inf
            if x > y:
                if y == sy:
                    if x >= sy:
                        temp_x = x
                        moves = 0
                        while temp_x > sx:
                            if temp_x % 2 != 0:
                                return inf 
                            temp_x //= 2
                            moves += 1
                        return moves if temp_x == sx else inf
                cnt = (x - y) // y
                return cnt + dfs(x - cnt * y, y)
            elif x < y:
                if x == sx:
                    if y >= sx:
                        temp_y = y
                        moves = 0
                        while temp_y > sy:
                            if temp_y % 2 != 0:
                                return inf  
                            temp_y //= 2
                            moves += 1
                        return moves if temp_y == sy else inf
                cnt = (y - x) // x
                return cnt + dfs(x, y - cnt * x)
            else:
                return inf

        ans = dfs(tx, ty)
        return ans if ans < inf else -1


class Solution:
    def minMoves(self, sx: int, sy: int, tx: int, ty: int) -> int:
        cnt = 0
        while tx >= sx and ty >= sy:
            if tx == sx and ty == sy:
                return cnt
            if tx > ty:
                if ty > sy:
                    if ty == 0:
                        return -1  
                    step = max((tx - sx) // ty, 1)
                    tx -= step * ty
                    cnt += step
                else:
                    if ty == 0:
                        return -1
                    if (tx - sx) % ty == 0:
                        return cnt + (tx - sx) // ty
                    else:
                        return -1
            else:
                if tx > sx:
                    if tx == 0:
                        return -1
                    step = max((ty - sy) // tx, 1)
                    ty -= step * tx
                    cnt += ty // tx
                else:
                    if tx == 0:
                        return -1
                    if (ty - sy) % tx == 0:
                        return cnt + (ty - sy) // tx
                    else:
                        return -1
        return -1


class Solution:
    def processQueries(
        self, c: int, connections: List[List[int]], queries: List[List[int]]
    ) -> List[int]:
        graph = [[] for _ in range(c + 1)]
        for u, v in connections:
            graph[u].append(v)
            graph[v].append(u)

        def find():
            visited = [False] * (c + 1)
            ret = {}
            comp_id = {}
            comps = []

            for i in range(1, c + 1):
                if not visited[i]:
                    component = []
                    stack = [i]
                    while stack:
                        node = stack.pop()
                        if not visited[node]:
                            visited[node] = True
                            component.append(node)
                            for neighbor in graph[node]:
                                if not visited[neighbor]:
                                    stack.append(neighbor)
                    component.sort()
                    comps.append(component)
                    for s in component:
                        ret[s] = component
                        comp_id[s] = len(comps) - 1
            return ret, comp_id, comps

        blocks, comp_id, comps = find()
        online = [True] * (c + 1)
        heaps = {}
        for idx, comp in enumerate(comps):
            heaps[idx] = comp[:]
            heapq.heapify(heaps[idx])

        ans = []
        for query in queries:
            if query[0] == 1:
                x = query[1]

                if online[x]:
                    ans.append(x)
                else:
                    cid = comp_id[x]
                    h = heaps[cid]

                    while h and not online[h[0]]:
                        heapq.heappop(h)

                    if h:
                        ans.append(h[0])
                    else:
                        ans.append(-1)
            elif query[0] == 2:
                x = query[1]
                online[x] = False

        return ans
