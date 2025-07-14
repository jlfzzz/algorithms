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


Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        ans = 0
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # 二进制状压vis
        @cache
        def dfs(left: int, right: int, vis: int) -> int:
            res = 0
            for v in g[left]:
                if vis >> v & 1:
                    continue
                for w in g[right]:
                    if vis >> w & 1 == 0 and v != w and label[w] == label[v]:
                        tv, tw = (
                            v,
                            w,
                        )  # 注意不能直接交换 v 和 w，否则下个循环的 v 就不是原来的 v 了
                        if tv > tw:  # 保证 tv < tw，减少状态个数和计算量
                            tv, tw = tw, tv
                        res = max(res, dfs(tv, tw, vis | 1 << v | 1 << w) + 2)
            return res

        for i in range(n):
            ans = Max(ans, dfs(i, i, 1 << i) + 1)
        for a, b in edges:
            if label[a] == label[b]:
                ans = Max(ans, dfs(a, b, 1 << a | 1 << b) + 2)
        return ans


class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        g = [[] for _ in range(n)]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        # 计算从 x 和 y 向两侧扩展，最多还能访问多少个节点（不算 x 和 y）
        @cache
        def dfs(x: int, y: int, vis: int) -> int:
            res = 0
            for v in g[x]:
                if vis >> v & 1:
                    continue
                for w in g[y]:
                    if vis >> w & 1 == 0 and v != w and label[w] == label[v]:
                        if v > w:  # 保证 v < w，减少状态个数和计算量
                            v, w = w, v
                        res = max(res, dfs(v, w, vis | 1 << v | 1 << w) + 2)
            return res

        ans = 0
        for x, to in enumerate(g):
            # 奇回文串，x 作为回文中心
            ans = max(ans, dfs(x, x, 1 << x) + 1)
            # 偶回文串，x 和 x 的邻居 y 作为回文中心
            for y in to:
                # 保证 x < y，减少状态个数和计算量
                if x < y and label[x] == label[y]:
                    ans = max(ans, dfs(x, y, 1 << x | 1 << y) + 2)
        return ans


class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        ans = 1

        dq = deque()
        vis = set()

        for center in range(n):
            t = (center, center, 1 << center)
            if t not in vis:
                dq.append(t)
                vis.add(t)

        for a, b in edges:
            if label[a] == label[b]:
                mask = (1 << a) | (1 << b)
                t = (a, b, mask)
                if t not in vis:
                    dq.append(t)
                    vis.add(t)
                    ans = max(ans, 2)

        while dq:
            left, right, vis_mask = dq.popleft()
            current_len = bin(vis_mask).count("1")
            ans = max(ans, current_len)

            for left_next in graph[left]:
                if not (vis_mask & (1 << left_next)):
                    for right_next in graph[right]:
                        if (
                            not (vis_mask & (1 << right_next))
                            and right_next != left_next
                            and label[left_next] == label[right_next]
                        ):

                            new_mask = vis_mask | (1 << left_next) | (1 << right_next)
                            t = (left_next, right_next, new_mask)

                            if t not in vis:
                                dq.append(t)
                                vis.add(t)

        return ans


class Solution:
    def maxLen(self, n: int, edges: List[List[int]], label: str) -> int:
        graph = [[] for _ in range(n)]
        for a, b in edges:
            graph[a].append(b)
            graph[b].append(a)

        @cache
        def expand(left: int, right: int, vis_mask: int) -> int:
            current_len = bin(vis_mask).count("1")
            res = current_len

            for left_next in graph[left]:
                if not (vis_mask & (1 << left_next)):
                    for right_next in graph[right]:
                        if (
                            not (vis_mask & (1 << right_next))
                            and right_next != left_next
                            and label[left_next] == label[right_next]
                        ):

                            new_mask = vis_mask | (1 << left_next) | (1 << right_next)
                            res = max(res, expand(left_next, right_next, new_mask))

            return res

        ans = 1

        for center in range(n):
            ans = max(ans, expand(center, center, 1 << center))

        for a, b in edges:
            if label[a] == label[b]:
                ans = max(ans, expand(a, b, (1 << a) | (1 << b)))

        return ans
