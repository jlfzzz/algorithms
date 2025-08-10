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
    def sortPermutation(self, nums: List[int]) -> int:
        n = len(nums)
        ans = (1 << 30) - 1

        for i in range(n):
            if nums[i] != i:
                ans = ans & (nums[i] & i)
        return ans if ans != (1 << 30) - 1 else 0©leetcode
