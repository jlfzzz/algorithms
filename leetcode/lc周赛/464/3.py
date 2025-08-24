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
    def maxValue(self, nums: List[int]) -> List[int]:
        n = len(nums)
        left_mx = [0] * n
        left_mx[0] = nums[0]
        mx = nums[0]
        for i in range(1, n):
            mx = max(mx, nums[i])
            left_mx[i] = mx

        right_mn = SortedSet()

        for i in range(n - 1, -1, -1):
            l_mx = left_mx[i]
            x = nums[i]
            nums[i] = max(nums[i], l_mx)

            if right_mn:
                idx = right_mn.bisect_left((nums[i], -1))
                if idx > 0:
                    mn, j = right_mn[idx - 1]
                    nums[i] = max(nums[i], left_mx[j])

            right_mn.add((x, i))
            left_mx[i] = max(l_mx, nums[i])
        return nums
