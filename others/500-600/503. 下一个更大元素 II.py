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
    def nextGreaterElements(self, nums: List[int]) -> List[int]:
        n = len(nums)
        dq = deque()
        ans = [-1] * n
        for i in range(n + n):
            j = i % n
            x = nums[j]
            while dq and nums[dq[-1]] < x:
                y = dq.pop()
                ans[y] = x
            dq.append(j)
        return ans
