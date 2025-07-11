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
    def trap(self, height: List[int]) -> int:
        dq = deque()
        ans = 0
        for i, x in enumerate(height):
            while dq and x >= height[dq[-1]]:
                y = dq.pop()
                if dq:
                    ans += (i - dq[-1] - 1) * (min(height[dq[-1]], x) - height[y])
            dq.append(i)
        return ans


class Solution:
    def trap(self, height: List[int]) -> int:
        n = len(height)
        right = [0] * n
        right[-1] = height[-1]
        for i in range(n - 2, -1, -1):
            right[i] = max(right[i + 1], height[i])
        left = 0
        ans = 0
        for i, x in enumerate(height):
            mn = min(left, right[i])
            if mn > x:
                ans += mn - x
            if x > left:
                left = x
        return ans
