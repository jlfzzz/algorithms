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

DIRS = [(-1, 0), (1, 0), (0, -1), (0, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def maximumsSplicedArray(self, nums1: List[int], nums2: List[int]) -> int:
        ans = sum(nums1)
        nums3 = [y - x for x, y in zip(nums1, nums2)]

        mx = 0
        dp = 0
        for x in nums3:
            dp = max(x, dp + x)
            mx = max(mx, dp)
        ans = max(ans, ans + mx)

        nums4 = [x - y for x, y in zip(nums1, nums2)]
        mx = dp = 0
        for x in nums4:
            dp = max(x, dp + x)
            mx = max(mx, dp)
        ans = max(ans, sum(nums2) + mx)
        return ans
