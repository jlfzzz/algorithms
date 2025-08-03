from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from operator import *
from typing import *
from queue import *
from string import *
from random import *
from sortedcontainers import *

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def minTime(self, s: str, order: List[int], k: int) -> int:
        n = len(s)
        # 使用SortedList，所有操作都是O(log n)
        added = SortedList([-1, n])

        cnt = [0] * (n + 1)

        for i in range(n):
            pos = order[i]

            # 找到pos应该插入的位置
            idx = added.bisect_left(pos)
            right = added[idx]  # pos右边的第一个元素
            left = added[idx - 1]  # pos左边的第一个元素

            len_l = pos - left
            len_r = right - pos

            # 防止溢出（虽然Python整数不溢出，但保持逻辑一致）
            if len_l >= float("inf") / 2:
                len_l = float("inf") / 2
            if len_r >= float("inf") / 2:
                len_r = float("inf") / 2

            cnt[i + 1] = cnt[i] + len_l * len_r

            # O(log n) 插入
            added.add(pos)

        # 找到第一个cnt[i] >= k的位置
        for i in range(n + 1):
            if cnt[i] >= k:
                return i - 1

        return -1


class Solution:
    def minTime(self, s: str, order: List[int], k: int) -> int:
        n = len(s)
        if n * (n + 1) // 2 < k:
            return -1

        star = [0] * n  # 避免在二分内部反复创建/初始化列表

        def check(m: int) -> bool:
            m += 1
            for j in range(m):
                star[order[j]] = m
            cnt = 0
            last = -1  # 上一个 '*' 的位置
            for i, x in enumerate(star):
                if x == m:  # s[i] 是 '*'
                    last = i
                cnt += last + 1
                if cnt >= k:  # 提前退出循环
                    return True
            return False

        left, right = -1, n
        while left + 1 < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid
        return right
