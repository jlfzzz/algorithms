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
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        heap = []
        curr = 0
        n = len(heights)
        for i in range(1, n):
            d = heights[i] - heights[i - 1]
            if d > 0:
                curr += d
                heappush(heap, -d)
                if curr > bricks:
                    if len(heap) == 0 or ladders == 0:
                        return i - 1
                    while ladders > 0 and heap and curr > bricks:
                        ladders -= 1
                        curr += heappop(heap)
                    if curr > bricks:
                        return i - 1

        return n - 1


class Solution:
    def furthestBuilding(self, heights: List[int], bricks: int, ladders: int) -> int:
        def canReach(mid: int) -> bool:
            climbs = []
            for i in range(mid):
                diff = heights[i + 1] - heights[i]
                if diff > 0:
                    heappush(climbs, diff)
                    if len(climbs) > ladders:
                        bricks_needed = heappop(climbs)
                        nonlocal_bricks[0] -= bricks_needed
                        if nonlocal_bricks[0] < 0:
                            return False
            return True

        lo, hi = 0, len(heights) - 1
        ans = 0
        while lo <= hi:
            mid = (lo + hi) // 2
            nonlocal_bricks = [bricks]  # 用列表传引用
            if canReach(mid):
                ans = mid
                lo = mid + 1
            else:
                hi = mid - 1
        return ans
