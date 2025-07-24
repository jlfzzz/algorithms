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
    def largestSumAfterKNegations(self, nums: List[int], k: int) -> int:
        nums.sort()
        i = 0
        while i < len(nums) and nums[i] < 0 and k > 0:
            nums[i] = -nums[i]
            k -= 1
            i += 1
        s = sum(nums)
        if k % 2 == 0:
            return s
        nums.sort()
        return s - nums[0] - nums[0]
