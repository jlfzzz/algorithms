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
    def removeDuplicates(self, nums: List[int]) -> int:
        n = len(nums)
        i = 0
        j = 0
        while i < n:
            x = nums[i]
            if x == nums[j]:
                i += 1
            else:
                j += 1
                nums[j] = x
                i += 1
        return j + 1
