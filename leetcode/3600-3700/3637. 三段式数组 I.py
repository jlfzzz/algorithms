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
    def isTrionic(self, nums: List[int]) -> bool:
        n = len(nums)
        i = 1
        while i < n and nums[i] > nums[i - 1]:
            i += 1
        if i == n or i == 1:
            return False

        # i -= 1
        t = i
        while i < n and nums[i] < nums[i - 1]:
            i += 1
        if i == n or t == i:
            return False
        # i -= 1
        t = i
        while i < n:
            if nums[i] <= nums[i - 1]:
                return False
            i += 1
        if i == t:
            return False
        return True
