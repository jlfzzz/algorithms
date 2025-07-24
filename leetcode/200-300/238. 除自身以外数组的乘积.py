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
Max = lambda a, b: b if b > a else a
Min = lambda a, b: b if b < a else a
INF = float("inf")
MOD = int(1e9 + 7)


class Solution:
    def productExceptSelf(self, nums: List[int]) -> List[int]:
        n = len(nums)
        right = [1] * (n + 1)
        for i in range(n - 1, -1, -1):
            right[i] = right[i + 1] * nums[i]

        left = 1
        ans = []
        for i in range(n):
            ans.append(left * right[i + 1])
            left *= nums[i]
        return ans
