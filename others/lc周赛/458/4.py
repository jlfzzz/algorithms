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
MOD = int(1e9 + 7)


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
