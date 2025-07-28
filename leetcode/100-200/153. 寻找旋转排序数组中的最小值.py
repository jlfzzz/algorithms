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

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def findMin(self, nums: List[int]) -> int:
        l, r = 0, len(nums)
        last = nums[-1]

        while l < r:
            m = (l + r) // 2
            if nums[m] > last:
                l = m + 1
            else:
                r = m
        return nums[l]
