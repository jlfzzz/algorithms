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
    def maxScore(self, nums: List[int], y: int) -> int:
        pre_even, pre_odd = -inf, -inf
        if nums[0] % 2:
            pre_odd = nums[0]
        else:
            pre_even = nums[0]
        n = len(nums)
        for i in range(1, n):
            x = nums[i]
            if x % 2:
                pre_odd = max(pre_odd + x, pre_even - y + x, pre_odd)
            else:
                pre_even = max(pre_even + x, pre_odd - y + x, pre_even)
        return max(pre_odd, pre_even)
