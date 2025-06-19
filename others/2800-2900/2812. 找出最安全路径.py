from collections import deque
import heapq
from typing import List
from math import *


class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        n = len(grid)
        if grid[0][0] == 1 or grid[n - 1][n - 1] == 1:
            return 0

        mn_dis = [[inf] * n for _ in range(n)]
        q = deque()

        for i in range(n):
            for j in range(n):
                if grid[i][j] == 1:
                    q.append((i, j, 0))
                    mn_dis[i][j] = 0

        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        # BFS
        while q:
            x, y, dist = q.popleft()

            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx < n and 0 <= ny < n:
                    new_dist = dist + 1
                    if new_dist < mn_dis[nx][ny]:
                        mn_dis[nx][ny] = new_dist
                        q.append((nx, ny, new_dist))

        heap = []
        visited = [[False] * n for _ in range(n)]

        heapq.heappush(heap, (-mn_dis[0][0], 0, 0))

        while heap:
            neg_dist, x, y = heapq.heappop(heap)
            current_dist = -neg_dist

            if visited[x][y]:
                continue
            visited[x][y] = True

            if x == n - 1 and y == n - 1:
                return current_dist
            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx < n and 0 <= ny < n and not visited[nx][ny]:
                    new_dist = min(current_dist, mn_dis[nx][ny])
                    heapq.heappush(heap, (-new_dist, nx, ny))

        return 0


class Solution:
    def maximumSafenessFactor(self, grid: List[List[int]]) -> int:
        n = len(grid)
        q = []
        dis = [[-1] * n for _ in range(n)]
        for i, row in enumerate(grid):
            for j, x in enumerate(row):
                if x:
                    q.append((i, j))
                    dis[i][j] = 0

        groups = [q]
        while q:  # 多源 BFS
            tmp = q
            q = []
            for i, j in tmp:
                for x, y in (i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1):
                    if 0 <= x < n and 0 <= y < n and dis[x][y] < 0:
                        q.append((x, y))
                        dis[x][y] = len(groups)
            groups.append(q)  # 相同 dis 分组记录

        # 并查集模板
        fa = list(range(n * n))

        def find(x: int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]

        for d in range(len(groups) - 2, 0, -1):
            for i, j in groups[d]:
                for x, y in (i + 1, j), (i - 1, j), (i, j + 1), (i, j - 1):
                    if 0 <= x < n and 0 <= y < n and dis[x][y] >= dis[i][j]:
                        fa[find(x * n + y)] = find(i * n + j)
            if find(0) == find(n * n - 1):  # 写这里判断更快些
                return d
        return 0
