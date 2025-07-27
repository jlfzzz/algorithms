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
    def countHillValley(self, nums: List[int]) -> int:
        # 26. 删除有序数组中的重复项
        k = 1
        for i in range(1, len(nums)):
            if nums[i] != nums[i - 1]:  # nums[i] 不是重复项
                nums[k] = nums[i]  # 保留 nums[i]
                k += 1

        ans = 0
        for i in range(1, k - 1):
            if (nums[i - 1] < nums[i]) == (nums[i] > nums[i + 1]):
                ans += 1
        return ans
