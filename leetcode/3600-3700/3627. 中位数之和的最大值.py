from collections import *
from functools import *
from math import *
from itertools import *
from heapq import *
from bisect import *
from typing import *
from queue import *
from string import *
from random import *

DIRS = [(1, 1), (1, -1), (-1, -1), (-1, 1)]
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float('inf')
MOD = int(1e9 + 7)


class Solution:
    def maximumMedianSum(self, nums: List[int]) -> int:
        n = len(nums)
        nums.sort()
        s = 0
        for i in range(n // 3):
            s += nums[n - 2 * (i + 1)]

        return s
