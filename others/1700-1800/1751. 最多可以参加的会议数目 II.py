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


# 手写 max 更快
max = lambda a, b: b if b > a else a


class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        events.sort(key=lambda e: e[1])  # 按照结束时间排序
        n = len(events)
        f = [[0] * (k + 1) for _ in range(n + 1)]
        for i, (start_day, _, value) in enumerate(events):
            p = bisect_left(
                events, start_day, hi=i, key=lambda e: e[1]
            )  # hi=i 表示二分上界为 i（默认为 n）
            for j in range(1, k + 1):
                # 为什么是 p 不是 p+1：上面算的是 >= start_day，-1 后得到 < start_day，但由于还要 +1，抵消了
                f[i + 1][j] = max(f[i][j], f[p][j - 1] + value)
        return f[n][k]


class Solution:
    def maxValue(self, events: List[List[int]], k: int) -> int:
        events.sort()
        n = len(events)

        @cache
        def dfs(i: int, use: int) -> int:
            if i == n or use == k:
                return 0
            start, end, val = events[i][0], events[i][1], events[i][2]
            res = dfs(i + 1, use)

            j = i + 1
            while j < n and events[j][0] <= end:
                j += 1

            res = max(res, dfs(j, use + 1) + val)

            return res

        return dfs(0, 0)
