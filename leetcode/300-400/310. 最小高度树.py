from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


from typing import List, Tuple
from math import inf


class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n == 1:
            return [0]

        # 构建无向图
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # max_2[i] 表示从节点 i 往下走的前两个最长路径和其来源节点
        max_2 = [[(0, -1), (0, -1)] for _ in range(n)]

        # 第一次 DFS：从下往上计算每个节点的前两大子树路径长度
        def dfs1(i: int, fa: int) -> Tuple[int, int]:
            res = [(0, -1), (0, -1)]
            for v in g[i]:
                if v == fa:
                    continue
                (child_max_len, _) = dfs1(v, i)
                current_len = child_max_len + 1
                if current_len > res[0][0]:
                    res[1] = res[0]
                    res[0] = (current_len, v)
                elif current_len > res[1][0]:
                    res[1] = (current_len, v)
            max_2[i] = res[:]
            return res[0]  # 返回最长路径

        dfs1(0, -1)

        # 第二次 DFS：换根，从父亲传来的路径往子节点传播
        ans_len = inf
        ans = []

        def dfs2(i: int, fa: int):
            nonlocal ans_len, ans

            mx1, from1 = max_2[i][0]
            mx2, from2 = max_2[i][1]

            # 更新答案
            if mx1 < ans_len:
                ans_len = mx1
                ans = [i]
            elif mx1 == ans_len:
                ans.append(i)

            # 向子节点传递信息（换根）
            for v in g[i]:
                if v == fa:
                    continue

                # 如果 v 是从 max_2[i][0] 这条最长路径来的
                if v == from1:
                    propagated = mx2 + 1
                else:
                    propagated = mx1 + 1

                # 尝试更新 max_2[v] 来自父亲的路径
                if propagated > max_2[v][0][0]:
                    max_2[v][1], max_2[v][0] = max_2[v][0], (propagated, i)
                elif propagated > max_2[v][1][0]:
                    max_2[v][1] = (propagated, i)

                dfs2(v, i)

        dfs2(0, -1)
        return ans


class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n == 1:
            return [0]
        g = [[] for _ in range(n)]
        degree = [0] * n
        for a, b in edges:
            g[a].append(b)
            g[b].append(a)
            degree[a] += 1
            degree[b] += 1
        q = deque(i for i in range(n) if degree[i] == 1)
        ans = []
        while q:
            ans.clear()
            for _ in range(len(q)):
                a = q.popleft()
                ans.append(a)
                for b in g[a]:
                    degree[b] -= 1
                    if degree[b] == 1:
                        q.append(b)
        return ans


class Solution:
    def findMinHeightTrees(self, n: int, edges: List[List[int]]) -> List[int]:
        if n == 1:
            return [0]

        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)
        parents = [0] * n

        def bfs(start: int):
            vis = [False] * n
            vis[start] = True
            q = deque([start])
            while q:
                x = q.popleft()
                for y in g[x]:
                    if not vis[y]:
                        vis[y] = True
                        parents[y] = x
                        q.append(y)
            return x

        x = bfs(0)  # 找到与节点 0 最远的节点 x
        y = bfs(x)  # 找到与节点 x 最远的节点 y

        path = []
        parents[x] = -1
        while y != -1:
            path.append(y)
            y = parents[y]
        m = len(path)
        return [path[m // 2]] if m % 2 else [path[m // 2 - 1], path[m // 2]]
