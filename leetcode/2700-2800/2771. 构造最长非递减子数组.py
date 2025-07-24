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
    def maxNonDecreasingLength(self, nums1: List[int], nums2: List[int]) -> int:
        n = len(nums1)
        f1, f2 = 1, 1
        ans = 1
        for i in range(1, n):
            f3, f4 = 1, 1
            x, y = nums1[i], nums2[i]
            if x >= nums1[i - 1]:
                f3 = f1 + 1
            if x >= nums2[i - 1]:
                f3 = max(f3, f2 + 1)

            if y >= nums1[i - 1]:
                f4 = f1 + 1
            if y >= nums2[i - 1]:
                f4 = max(f4, f2 + 1)

            ans = max(ans, f3, f4)
            f1, f2 = f3, f4
        return ans
