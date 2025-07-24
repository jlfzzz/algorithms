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
    def maxFreeTime(
        self, eventTime: int, startTime: List[int], endTime: List[int]
    ) -> int:
        n = len(startTime)
        free = [0] * (n + 1)
        free[0] = startTime[0]
        for i in range(1, n):
            free[i] = startTime[i] - endTime[i - 1]
        free[n] = eventTime - endTime[-1]
        ans = 0
        rightMax = [-inf] * n
        rightMax[-1] = free[-1]
        for i in range(n - 2, -1, -1):
            rightMax[i] = max(rightMax[i + 1], free[i + 1])
        leftMax = [-inf] * n
        leftMax[0] = free[0]
        for i in range(1, n):
            leftMax[i] = max(leftMax[i - 1], free[i])
        for i, (s, e) in enumerate(zip(startTime, endTime)):
            diff = e - s
            ans = max(ans, free[i] + free[i + 1])
            l = leftMax[i - 1] if i >= 1 else -1
            r = rightMax[i + 1] if i + 1 < n else -1
            if l >= diff or r >= diff:
                ans = max(ans, free[i] + free[i + 1] + diff)
        return ans
